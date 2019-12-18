#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_stringbuf_t ;
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_repos_t ;
typedef  int /*<<< orphan*/  (* svn_repos_authz_func_t ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *) ;
struct TYPE_8__ {scalar_t__ range_end; scalar_t__ range_start; char const* path; } ;
typedef  TYPE_2__ svn_location_segment_t ;
typedef  int /*<<< orphan*/  svn_location_segment_receiver_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_fs_root_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_ERR_ASSERT (int) ; 
 int /*<<< orphan*/  SVN_ERR_FS_NO_SUCH_REVISION ; 
 scalar_t__ SVN_INVALID_REVNUM ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_VA_NULL ; 
 int /*<<< orphan*/  _ (char*) ; 
 TYPE_2__* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* apr_pstrcat (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 char* apr_pstrmemdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_readability (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,void*,int /*<<< orphan*/ *),void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maybe_crop_and_send_segment (TYPE_2__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_error_createf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  svn_fs_node_origin_rev (scalar_t__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_revision_root (int /*<<< orphan*/ **,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_youngest_rev (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_pool_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_repos__prev_location (scalar_t__*,char const**,scalar_t__*,int /*<<< orphan*/ *,scalar_t__,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_repos_fs (int /*<<< orphan*/ *) ; 
 TYPE_1__* svn_stringbuf_create (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stringbuf_set (TYPE_1__*,char const*) ; 

svn_error_t *
svn_repos_node_location_segments(svn_repos_t *repos,
                                 const char *path,
                                 svn_revnum_t peg_revision,
                                 svn_revnum_t start_rev,
                                 svn_revnum_t end_rev,
                                 svn_location_segment_receiver_t receiver,
                                 void *receiver_baton,
                                 svn_repos_authz_func_t authz_read_func,
                                 void *authz_read_baton,
                                 apr_pool_t *pool)
{
  svn_fs_t *fs = svn_repos_fs(repos);
  svn_stringbuf_t *current_path;
  svn_revnum_t youngest_rev, current_rev;
  apr_pool_t *subpool;

  SVN_ERR(svn_fs_youngest_rev(&youngest_rev, fs, pool));

  /* No PEG_REVISION?  We'll use HEAD. */
  if (! SVN_IS_VALID_REVNUM(peg_revision))
    peg_revision = youngest_rev;

  if (peg_revision > youngest_rev)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("No such revision %ld"), peg_revision);

  /* No START_REV?  We'll use peg rev. */
  if (! SVN_IS_VALID_REVNUM(start_rev))
    start_rev = peg_revision;
  else if (start_rev > peg_revision)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("No such revision %ld"), start_rev);

  /* No END_REV?  We'll use 0. */
  if (! SVN_IS_VALID_REVNUM(end_rev))
    end_rev = 0;
  else if (end_rev > start_rev)
    return svn_error_createf(SVN_ERR_FS_NO_SUCH_REVISION, NULL,
                             _("No such revision %ld"), end_rev);

  /* Are the revision properly ordered?  They better be -- the API
     demands it. */
  SVN_ERR_ASSERT(end_rev <= start_rev);
  SVN_ERR_ASSERT(start_rev <= peg_revision);

  /* Ensure that PATH is absolute, because our path-math will depend
     on that being the case.  */
  if (*path != '/')
    path = apr_pstrcat(pool, "/", path, SVN_VA_NULL);

  /* Auth check. */
  if (authz_read_func)
    {
      svn_fs_root_t *peg_root;
      SVN_ERR(svn_fs_revision_root(&peg_root, fs, peg_revision, pool));
      SVN_ERR(check_readability(peg_root, path,
                                authz_read_func, authz_read_baton, pool));
    }

  /* Okay, let's get searching! */
  subpool = svn_pool_create(pool);
  current_rev = peg_revision;
  current_path = svn_stringbuf_create(path, pool);
  while (current_rev >= end_rev)
    {
      svn_revnum_t appeared_rev, prev_rev;
      const char *cur_path, *prev_path;
      svn_location_segment_t *segment;

      svn_pool_clear(subpool);

      cur_path = apr_pstrmemdup(subpool, current_path->data,
                                current_path->len);
      segment = apr_pcalloc(subpool, sizeof(*segment));
      segment->range_end = current_rev;
      segment->range_start = end_rev;
      /* segment path should be absolute without leading '/'. */
      segment->path = cur_path + 1;

      SVN_ERR(svn_repos__prev_location(&appeared_rev, &prev_path, &prev_rev,
                                       fs, current_rev, cur_path, subpool));

      /* If there are no previous locations for this thing (meaning,
         it originated at the current path), then we simply need to
         find its revision of origin to populate our final segment.
         Otherwise, the APPEARED_REV is the start of current segment's
         range. */
      if (! prev_path)
        {
          svn_fs_root_t *revroot;
          SVN_ERR(svn_fs_revision_root(&revroot, fs, current_rev, subpool));
          SVN_ERR(svn_fs_node_origin_rev(&(segment->range_start), revroot,
                                         cur_path, subpool));
          if (segment->range_start < end_rev)
            segment->range_start = end_rev;
          current_rev = SVN_INVALID_REVNUM;
        }
      else
        {
          segment->range_start = appeared_rev;
          svn_stringbuf_set(current_path, prev_path);
          current_rev = prev_rev;
        }

      /* Report our segment, providing it passes authz muster. */
      if (authz_read_func)
        {
          svn_boolean_t readable;
          svn_fs_root_t *cur_rev_root;

          /* authz_read_func requires path to have a leading slash. */
          const char *abs_path = apr_pstrcat(subpool, "/", segment->path,
                                             SVN_VA_NULL);

          SVN_ERR(svn_fs_revision_root(&cur_rev_root, fs,
                                       segment->range_end, subpool));
          SVN_ERR(authz_read_func(&readable, cur_rev_root, abs_path,
                                  authz_read_baton, subpool));
          if (! readable)
            return SVN_NO_ERROR;
        }

      /* Transmit the segment (if it's within the scope of our concern). */
      SVN_ERR(maybe_crop_and_send_segment(segment, start_rev, end_rev,
                                          receiver, receiver_baton, subpool));

      /* If we've set CURRENT_REV to SVN_INVALID_REVNUM, we're done
         (and didn't ever reach END_REV).  */
      if (! SVN_IS_VALID_REVNUM(current_rev))
        break;

      /* If there's a gap in the history, we need to report as much
         (if the gap is within the scope of our concern). */
      if (segment->range_start - current_rev > 1)
        {
          svn_location_segment_t *gap_segment;
          gap_segment = apr_pcalloc(subpool, sizeof(*gap_segment));
          gap_segment->range_end = segment->range_start - 1;
          gap_segment->range_start = current_rev + 1;
          gap_segment->path = NULL;
          SVN_ERR(maybe_crop_and_send_segment(gap_segment, start_rev, end_rev,
                                              receiver, receiver_baton,
                                              subpool));
        }
    }
  svn_pool_destroy(subpool);
  return SVN_NO_ERROR;
}