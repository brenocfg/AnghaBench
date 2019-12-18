#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_revnum_t ;
struct TYPE_16__ {int /*<<< orphan*/  number; int /*<<< orphan*/  change_set; } ;
struct TYPE_18__ {TYPE_1__ id; int /*<<< orphan*/  expanded_size; } ;
typedef  TYPE_3__ svn_fs_x__representation_t ;
struct TYPE_19__ {int /*<<< orphan*/  second; int /*<<< orphan*/  revision; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_4__ svn_fs_x__pair_cache_key_t ;
struct TYPE_20__ {int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_5__ svn_fs_x__data_t ;
struct TYPE_21__ {TYPE_5__* fsap_data; } ;
typedef  TYPE_6__ svn_fs_t ;
typedef  int /*<<< orphan*/  svn_filesize_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_17__ {int /*<<< orphan*/  revision; } ;
struct TYPE_22__ {TYPE_2__ fulltext_cache_key; int /*<<< orphan*/  fulltext_cache; } ;
typedef  TYPE_7__ rep_read_baton_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ fulltext_size_is_cachable (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rep_read_contents ; 
 int /*<<< orphan*/  rep_read_contents_close ; 
 int /*<<< orphan*/  rep_read_get_baton (TYPE_7__**,TYPE_6__*,TYPE_3__*,TYPE_4__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_fs_x__get_revnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * svn_stream_create (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * svn_stream_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_stream_set_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_set_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

svn_error_t *
svn_fs_x__get_contents(svn_stream_t **contents_p,
                       svn_fs_t *fs,
                       svn_fs_x__representation_t *rep,
                       svn_boolean_t cache_fulltext,
                       apr_pool_t *result_pool)
{
  if (! rep)
    {
      *contents_p = svn_stream_empty(result_pool);
    }
  else
    {
      svn_fs_x__data_t *ffd = fs->fsap_data;
      svn_filesize_t len = rep->expanded_size;
      rep_read_baton_t *rb;
      svn_revnum_t revision = svn_fs_x__get_revnum(rep->id.change_set);

      svn_fs_x__pair_cache_key_t fulltext_cache_key = { 0 };
      fulltext_cache_key.revision = revision;
      fulltext_cache_key.second = rep->id.number;

      /* Initialize the reader baton.  Some members may added lazily
       * while reading from the stream */
      SVN_ERR(rep_read_get_baton(&rb, fs, rep, fulltext_cache_key,
                                 result_pool));

      /* Make the stream attempt fulltext cache lookups if the fulltext
       * is cacheable.  If it is not, then also don't try to buffer and
       * cache it. */
      if (   cache_fulltext
          && SVN_IS_VALID_REVNUM(revision)
          && fulltext_size_is_cachable(ffd, len))
        {
          rb->fulltext_cache = ffd->fulltext_cache;
        }
      else
        {
          /* This will also prevent the reconstructed fulltext from being
             put into the cache. */
          rb->fulltext_cache_key.revision = SVN_INVALID_REVNUM;
        }

      *contents_p = svn_stream_create(rb, result_pool);
      svn_stream_set_read2(*contents_p, NULL /* only full read support */,
                           rep_read_contents);
      svn_stream_set_close(*contents_p, rep_read_contents_close);
    }

  return SVN_NO_ERROR;
}