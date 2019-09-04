#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct lev_storage_file {long long secret; scalar_t__ type; int content_type; scalar_t__ local_id; int /*<<< orphan*/  mtime; int /*<<< orphan*/  size; scalar_t__ data; } ;
struct connection {int dummy; } ;
struct TYPE_7__ {scalar_t__ local_id; TYPE_1__* B; int /*<<< orphan*/  offset; int /*<<< orphan*/ * data; scalar_t__ corrupted; scalar_t__ aio; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_2__ metafile_t ;
struct TYPE_6__ {int /*<<< orphan*/  volume_id; int /*<<< orphan*/  abs_filename; } ;

/* Variables and functions */
 scalar_t__ LEV_STORAGE_FILE ; 
 long long STORAGE_SECRET_MASK ; 
 int ct_last ; 
 int http_try_x_accel_redirect (struct connection*,TYPE_2__*,long long,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  redirect_retries_content_type ; 
 int /*<<< orphan*/  redirect_retries_corrupted ; 
 int /*<<< orphan*/  redirect_retries_local_id ; 
 int /*<<< orphan*/  redirect_retries_meta_aio ; 
 int /*<<< orphan*/  redirect_retries_secret ; 
 int /*<<< orphan*/  redirect_retries_type ; 
 int /*<<< orphan*/  update_binlog_read_stat (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int /*<<< orphan*/  write_http_doc (struct connection*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int http_return_file (struct connection *c, metafile_t *meta, long long secret, int content_type) {
  if (meta == NULL) {
    vkprintf (1, "http_return_file: meta == NULL\n");
    return -500;
  }
  meta->refcnt--;
  if (meta->aio) {
    vkprintf (2, "Metafile timeout error %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_meta_aio);
  }
  if (meta->corrupted) {
    vkprintf (2, "Metafile read error %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_corrupted);
  }

  const struct lev_storage_file *E = (struct lev_storage_file *) &meta->data[0];

  if ((secret ^ E->secret) & STORAGE_SECRET_MASK) {
    vkprintf (2, "Metafiles 2 high bytes of secret is corrupted, %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_secret);
  }

  if (E->type != LEV_STORAGE_FILE) {
    vkprintf (2, "E->type isn't LEV_STORAGE_FILE %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_type);
  }
  if (E->content_type >= ct_last || E->content_type < 0) {
    vkprintf (2, "Illegal E->content_type in %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_content_type);
  }
  if (E->local_id != meta->local_id) {
    vkprintf (2, "local_id not matched %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return http_try_x_accel_redirect (c, meta, secret, content_type, -500, &redirect_retries_local_id);
  }
  update_binlog_read_stat (meta, 1);
  if (E->secret != secret) {
    vkprintf (2, "secret not matched %s, offset: %lld, volume_id: %lld\n", meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return -403;
  }
  if (E->content_type != content_type) {
    vkprintf (2, "E->content_type (%d) != content_type (%d) %s, offset: %lld, volume_id: %lld\n", E->content_type, content_type, meta->B->abs_filename, meta->offset, meta->B->volume_id);
    return -404;
  }
  vkprintf (3, "E->size = %d\n", E->size);

  write_http_doc (c, (void *) E->data, E->size, E->mtime, E->content_type);
  return 0;
}