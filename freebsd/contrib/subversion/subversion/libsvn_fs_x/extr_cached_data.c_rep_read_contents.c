#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_1__ svn_fs_x__data_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct TYPE_15__ {int /*<<< orphan*/  digest; int /*<<< orphan*/  kind; } ;
typedef  TYPE_2__ svn_checksum_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_16__ {scalar_t__ off; scalar_t__ len; int /*<<< orphan*/ * current_fulltext; int /*<<< orphan*/  scratch_pool; int /*<<< orphan*/  fulltext_cache_key; TYPE_12__* fs; int /*<<< orphan*/  md5_checksum_ctx; scalar_t__ checksum_finalized; int /*<<< orphan*/  md5_digest; int /*<<< orphan*/  fulltext_delivered; int /*<<< orphan*/  filehandle_pool; int /*<<< orphan*/  rep; int /*<<< orphan*/  src_state; int /*<<< orphan*/  base_window; int /*<<< orphan*/  rs_list; int /*<<< orphan*/ * fulltext_cache; } ;
typedef  TYPE_3__ rep_read_baton_t ;
typedef  int /*<<< orphan*/  apr_size_t ;
struct TYPE_13__ {TYPE_1__* fsap_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_FS_CORRUPT ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  build_rep_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_contents_from_fulltext (scalar_t__*,TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_contents_from_windows (TYPE_3__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip_contents (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_cache__set (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_final (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_match (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  svn_checksum_md5 ; 
 int /*<<< orphan*/  svn_checksum_mismatch_err (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_checksum_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_appendbytes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
rep_read_contents(void *baton,
                  char *buf,
                  apr_size_t *len)
{
  rep_read_baton_t *rb = baton;

  /* Get data from the fulltext cache for as long as we can. */
  if (rb->fulltext_cache)
    {
      svn_boolean_t cached;
      SVN_ERR(get_contents_from_fulltext(&cached, rb, buf, len));
      if (cached)
        return SVN_NO_ERROR;

      /* Cache miss.  From now on, we will never read from the fulltext
       * cache for this representation anymore. */
      rb->fulltext_cache = NULL;
    }

  /* No fulltext cache to help us.  We must read from the window stream. */
  if (!rb->rs_list)
    {
      /* Window stream not initialized, yet.  Do it now. */
      SVN_ERR(build_rep_list(&rb->rs_list, &rb->base_window,
                             &rb->src_state, rb->fs, &rb->rep,
                             rb->filehandle_pool, rb->scratch_pool));

      /* In case we did read from the fulltext cache before, make the
       * window stream catch up.  Also, initialize the fulltext buffer
       * if we want to cache the fulltext at the end. */
      SVN_ERR(skip_contents(rb, rb->fulltext_delivered));
    }

  /* Get the next block of data.
   * Keep in mind that the representation might be empty and leave us
   * already positioned at the end of the rep. */
  if (rb->off == rb->len)
    *len = 0;
  else
    SVN_ERR(get_contents_from_windows(rb, buf, len));

  if (rb->current_fulltext)
    svn_stringbuf_appendbytes(rb->current_fulltext, buf, *len);

  /* Perform checksumming.  We want to check the checksum as soon as
     the last byte of data is read, in case the caller never performs
     a short read, but we don't want to finalize the MD5 context
     twice. */
  if (!rb->checksum_finalized)
    {
      SVN_ERR(svn_checksum_update(rb->md5_checksum_ctx, buf, *len));
      rb->off += *len;
      if (rb->off == rb->len)
        {
          svn_checksum_t *md5_checksum;
          svn_checksum_t expected;
          expected.kind = svn_checksum_md5;
          expected.digest = rb->md5_digest;

          rb->checksum_finalized = TRUE;
          SVN_ERR(svn_checksum_final(&md5_checksum, rb->md5_checksum_ctx,
                                     rb->scratch_pool));
          if (!svn_checksum_match(md5_checksum, &expected))
            return svn_error_create(SVN_ERR_FS_CORRUPT,
                    svn_checksum_mismatch_err(&expected, md5_checksum,
                        rb->scratch_pool,
                        _("Checksum mismatch while reading representation")),
                    NULL);
        }
    }

  if (rb->off == rb->len && rb->current_fulltext)
    {
      svn_fs_x__data_t *ffd = rb->fs->fsap_data;
      SVN_ERR(svn_cache__set(ffd->fulltext_cache, &rb->fulltext_cache_key,
                             rb->current_fulltext, rb->scratch_pool));
      rb->current_fulltext = NULL;
    }

  return SVN_NO_ERROR;
}