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
typedef  int /*<<< orphan*/  svn_stream_t ;
typedef  int /*<<< orphan*/  svn_fs_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
struct TYPE_6__ {scalar_t__ expanded_size; int /*<<< orphan*/  sha1_digest; scalar_t__ has_sha1; int /*<<< orphan*/  md5_digest; } ;
typedef  TYPE_1__ representation_t ;
struct TYPE_7__ {int /*<<< orphan*/  id; TYPE_1__* data_rep; } ;
typedef  TYPE_2__ node_revision_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 scalar_t__ TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  svn_fs_fs__get_contents (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_fs_fs__id_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_stream_contents_same2 (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

svn_error_t *
svn_fs_fs__file_text_rep_equal(svn_boolean_t *equal,
                               svn_fs_t *fs,
                               node_revision_t *a,
                               node_revision_t *b,
                               apr_pool_t *scratch_pool)
{
  svn_stream_t *contents_a, *contents_b;
  representation_t *rep_a = a->data_rep;
  representation_t *rep_b = b->data_rep;
  svn_boolean_t a_empty = !rep_a || rep_a->expanded_size == 0;
  svn_boolean_t b_empty = !rep_b || rep_b->expanded_size == 0;

  /* This makes sure that neither rep will be NULL later on */
  if (a_empty && b_empty)
    {
      *equal = TRUE;
      return SVN_NO_ERROR;
    }

  if (a_empty != b_empty)
    {
      *equal = FALSE;
      return SVN_NO_ERROR;
    }

  /* File text representations always know their checksums - even in a txn. */
  if (memcmp(rep_a->md5_digest, rep_b->md5_digest, sizeof(rep_a->md5_digest)))
    {
      *equal = FALSE;
      return SVN_NO_ERROR;
    }

  /* Paranoia. Compare SHA1 checksums because that's the level of
     confidence we require for e.g. the working copy. */
  if (rep_a->has_sha1 && rep_b->has_sha1)
    {
      *equal = memcmp(rep_a->sha1_digest, rep_b->sha1_digest,
                      sizeof(rep_a->sha1_digest)) == 0;
      return SVN_NO_ERROR;
    }

  /* Same path in same rev or txn? */
  if (svn_fs_fs__id_eq(a->id, b->id))
    {
      *equal = TRUE;
      return SVN_NO_ERROR;
    }

  SVN_ERR(svn_fs_fs__get_contents(&contents_a, fs, rep_a, TRUE,
                                  scratch_pool));
  SVN_ERR(svn_fs_fs__get_contents(&contents_b, fs, rep_b, TRUE,
                                  scratch_pool));
  SVN_ERR(svn_stream_contents_same2(equal, contents_a, contents_b,
                                   scratch_pool));

  return SVN_NO_ERROR;
}