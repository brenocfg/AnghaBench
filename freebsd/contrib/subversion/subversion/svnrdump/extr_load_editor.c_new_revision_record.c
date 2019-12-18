#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ svn_revnum_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {scalar_t__ rev; int /*<<< orphan*/  pool; int /*<<< orphan*/  revprop_table; struct parse_baton* pb; scalar_t__ rev_offset; int /*<<< orphan*/ * db; } ;
struct parse_baton {scalar_t__ oldest_dumpstream_rev; int /*<<< orphan*/ * commit_edit_baton; int /*<<< orphan*/ * commit_editor; int /*<<< orphan*/  session; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  scalar_t__ apr_int32_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_REVISION_NUMBER ; 
 scalar_t__ SVN_STR_TO_REV (char const*) ; 
 int /*<<< orphan*/  apr_hash_make (int /*<<< orphan*/ ) ; 
 struct revision_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_pool_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_ra_get_latest_revnum (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
new_revision_record(void **revision_baton,
                    apr_hash_t *headers,
                    void *parse_baton,
                    apr_pool_t *pool)
{
  struct revision_baton *rb;
  struct parse_baton *pb;
  const char *rev_str;
  svn_revnum_t head_rev;

  rb = apr_pcalloc(pool, sizeof(*rb));
  pb = parse_baton;
  rb->pool = svn_pool_create(pool);
  rb->pb = pb;
  rb->db = NULL;

  rev_str = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_REVISION_NUMBER);
  if (rev_str)
    rb->rev = SVN_STR_TO_REV(rev_str);

  SVN_ERR(svn_ra_get_latest_revnum(pb->session, &head_rev, pool));

  /* FIXME: This is a lame fallback loading multiple segments of dump in
     several separate operations. It is highly susceptible to race conditions.
     Calculate the revision 'offset' for finding copyfrom sources.
     It might be positive or negative. */
  rb->rev_offset = (apr_int32_t) ((rb->rev) - (head_rev + 1));

  /* Stash the oldest (non-zero) dumpstream revision seen. */
  if ((rb->rev > 0) && (!SVN_IS_VALID_REVNUM(pb->oldest_dumpstream_rev)))
    pb->oldest_dumpstream_rev = rb->rev;

  /* Set the commit_editor/ commit_edit_baton to NULL and wait for
     them to be created in new_node_record */
  rb->pb->commit_editor = NULL;
  rb->pb->commit_edit_baton = NULL;
  rb->revprop_table = apr_hash_make(rb->pool);

  *revision_baton = rb;
  return SVN_NO_ERROR;
}