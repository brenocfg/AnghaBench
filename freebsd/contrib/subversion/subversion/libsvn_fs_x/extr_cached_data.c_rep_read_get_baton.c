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
struct TYPE_6__ {int /*<<< orphan*/  expanded_size; int /*<<< orphan*/  md5_digest; } ;
typedef  TYPE_1__ svn_fs_x__representation_t ;
typedef  int /*<<< orphan*/  svn_fs_x__pair_cache_key_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_7__ {int /*<<< orphan*/ * current_fulltext; scalar_t__ fulltext_delivered; int /*<<< orphan*/ * fulltext_cache; void* filehandle_pool; void* scratch_pool; int /*<<< orphan*/  fulltext_cache_key; scalar_t__ off; int /*<<< orphan*/  len; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  checksum_finalized; int /*<<< orphan*/  md5_checksum_ctx; int /*<<< orphan*/ * buf; scalar_t__ chunk_index; int /*<<< orphan*/ * base_window; TYPE_1__ rep; int /*<<< orphan*/ * fs; } ;
typedef  TYPE_2__ rep_read_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_checksum_ctx_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 void* svn_pool_create (int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
rep_read_get_baton(rep_read_baton_t **rb_p,
                   svn_fs_t *fs,
                   svn_fs_x__representation_t *rep,
                   svn_fs_x__pair_cache_key_t fulltext_cache_key,
                   apr_pool_t *result_pool)
{
  rep_read_baton_t *b;

  b = apr_pcalloc(result_pool, sizeof(*b));
  b->fs = fs;
  b->rep = *rep;
  b->base_window = NULL;
  b->chunk_index = 0;
  b->buf = NULL;
  b->md5_checksum_ctx = svn_checksum_ctx_create(svn_checksum_md5,
                                                result_pool);
  b->checksum_finalized = FALSE;
  memcpy(b->md5_digest, rep->md5_digest, sizeof(rep->md5_digest));
  b->len = rep->expanded_size;
  b->off = 0;
  b->fulltext_cache_key = fulltext_cache_key;

  /* Clearable sub-pools.  Since they have to remain valid for as long as B
     lives, we can't take them from some scratch pool.  The caller of this
     function will have no control over how those subpools will be used. */
  b->scratch_pool = svn_pool_create(result_pool);
  b->filehandle_pool = svn_pool_create(result_pool);
  b->fulltext_cache = NULL;
  b->fulltext_delivered = 0;
  b->current_fulltext = NULL;

  /* Save our output baton. */
  *rb_p = b;

  return SVN_NO_ERROR;
}