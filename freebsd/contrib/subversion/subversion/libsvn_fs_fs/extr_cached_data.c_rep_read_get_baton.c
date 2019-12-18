#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_3__ {int /*<<< orphan*/  expanded_size; int /*<<< orphan*/  md5_digest; } ;
struct rep_read_baton {int /*<<< orphan*/ * current_fulltext; scalar_t__ fulltext_delivered; int /*<<< orphan*/ * fulltext_cache; void* filehandle_pool; void* pool; int /*<<< orphan*/  fulltext_cache_key; scalar_t__ off; int /*<<< orphan*/  len; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  checksum_finalized; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/ * buf; scalar_t__ chunk_index; int /*<<< orphan*/ * base_window; TYPE_1__ rep; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_1__ representation_t ;
typedef  int /*<<< orphan*/  pair_cache_key_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 struct rep_read_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rep_read_get_baton(struct rep_read_baton **rb_p,
                   svn_fs_t *fs,
                   representation_t *rep,
                   pair_cache_key_t fulltext_cache_key,
                   apr_pool_t *pool)
{
  struct rep_read_baton *b;

  b = apr_pcalloc(pool, sizeof(*b));
  b->fs = fs;
  b->rep = *rep;
  b->base_window = NULL;
  b->chunk_index = 0;
  b->buf = NULL;
  b->md5_checksum_ctx = svn_checksum_ctx_create(svn_checksum_md5, pool);
  b->checksum_finalized = FALSE;
  memcpy(b->md5_digest, rep->md5_digest, sizeof(rep->md5_digest));
  b->len = rep->expanded_size;
  b->off = 0;
  b->fulltext_cache_key = fulltext_cache_key;
  b->pool = svn_pool_create(pool);
  b->filehandle_pool = svn_pool_create(pool);
  b->fulltext_cache = NULL;
  b->fulltext_delivered = 0;
  b->current_fulltext = NULL;

  /* Save our output baton. */
  *rb_p = b;

  return SVN_NO_ERROR;
}