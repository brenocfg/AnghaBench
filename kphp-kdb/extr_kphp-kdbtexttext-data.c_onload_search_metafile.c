#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int user_id; TYPE_3__* search_mf; scalar_t__ dir_entry; } ;
typedef  TYPE_2__ user_t ;
struct file_user_list_entry_search {int user_search_size; int /*<<< orphan*/  user_data_size; int /*<<< orphan*/  user_data_offset; } ;
struct file_search_header {scalar_t__ magic; int words_num; } ;
struct connection {int dummy; } ;
struct aio_connection {scalar_t__ basic_type; scalar_t__ extra; } ;
struct TYPE_8__ {scalar_t__ mf_type; int len; int data; struct aio_connection* aio; TYPE_1__* next; TYPE_1__* prev; TYPE_2__* user; } ;
typedef  TYPE_3__ core_mf_t ;
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* prev; } ;

/* Variables and functions */
 scalar_t__ FILE_USER_SEARCH_MAGIC ; 
 scalar_t__ MF_SEARCH ; 
 int /*<<< orphan*/  active_aio_queries ; 
 int /*<<< orphan*/  aio_crc_errors ; 
 int /*<<< orphan*/  aio_read_errors ; 
 int /*<<< orphan*/  allocated_search_metafile_bytes ; 
 int /*<<< orphan*/  assert (int) ; 
 unsigned int compute_crc32 (int,int) ; 
 scalar_t__ ct_aio ; 
 int cur_search_metafile_bytes ; 
 int /*<<< orphan*/  cur_search_metafiles ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 scalar_t__ get_search_metafile (TYPE_2__*) ; 
 int idx_crc_enabled ; 
 int idx_search_enabled ; 
 int metafile_crc_check_size_threshold ; 
 int /*<<< orphan*/  stderr ; 
 int tot_search_metafile_bytes ; 
 int /*<<< orphan*/  tot_search_metafiles ; 
 scalar_t__ verbosity ; 

int onload_search_metafile (struct connection *c, int read_bytes) {
  if (verbosity > 0) {
    fprintf (stderr, "onload_search_metafile(%p,%d)\n", c, read_bytes);
  }
  assert (idx_search_enabled);

  struct aio_connection *a = (struct aio_connection *)c;
  core_mf_t *M = (core_mf_t *) a->extra;
  user_t *U = M->user;

  assert (a->basic_type == ct_aio);
  assert (M->mf_type == MF_SEARCH);
  assert (U->search_mf == M);
  assert (M->aio == a);

  struct file_user_list_entry_search *D = (struct file_user_list_entry_search *) U->dir_entry;

  unsigned data_crc32, disk_crc32;
  if (idx_crc_enabled && read_bytes == M->len && read_bytes < metafile_crc_check_size_threshold) {
    assert (read_bytes >= 4);
    disk_crc32 = *((unsigned *) (M->data + read_bytes - 4));
    data_crc32 = compute_crc32 (M->data, read_bytes - 4);
  } else {
    disk_crc32 = data_crc32 = 0;
  }

  assert (M->len == D->user_search_size + idx_crc_enabled * 4);
  if (read_bytes != M->len || disk_crc32 != data_crc32) {
    aio_read_errors++;
    if (verbosity >= 0) {
      fprintf (stderr, "ERROR reading user %d search data from index at position %lld [pending aio queries: %lld]: read %d bytes out of %d: %m\n", U->user_id, D->user_data_offset + D->user_data_size, active_aio_queries, read_bytes, M->len);
    }
    if (disk_crc32 != data_crc32) {
      aio_crc_errors++;
      if (verbosity >= 0) {
	fprintf (stderr, "CRC mismatch: expected %08x, found %08x\n", disk_crc32, data_crc32);
      }
      assert (disk_crc32 == data_crc32);
    }

    allocated_search_metafile_bytes -= M->len;
    M->next->prev = M->prev;
    M->prev->next = M->next;
    M->prev = M->next = 0;
    M->aio = 0;

    free (M);
    U->search_mf = 0;

    return 0;
  }

  if (verbosity > 0) {
    fprintf (stderr, "*** Read user %d search data from index at position %lld: read %d bytes\n", U->user_id, D->user_data_offset + D->user_data_size, read_bytes);
  }

  M->aio = 0;

  struct file_search_header *H = (struct file_search_header *) get_search_metafile (U);

  assert (H->magic == FILE_USER_SEARCH_MAGIC);
  assert (H->words_num > 0);
  assert (H->words_num <= (read_bytes >> 2) - 2);

  cur_search_metafile_bytes += read_bytes;
  tot_search_metafile_bytes += read_bytes;
  cur_search_metafiles++;
  tot_search_metafiles++;

  if (U->user_id == 92226304) {
    // write (1, M->data, M->len);
    // exit (0);
  }

  return 1;
}