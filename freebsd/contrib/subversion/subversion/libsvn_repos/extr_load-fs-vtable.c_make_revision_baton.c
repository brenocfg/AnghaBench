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
typedef  int /*<<< orphan*/  svn_prop_t ;
struct revision_baton {scalar_t__ rev; int skipped; int /*<<< orphan*/ * pool; int /*<<< orphan*/  revprops; struct parse_baton* pb; } ;
struct parse_baton {scalar_t__ start_rev; scalar_t__ end_rev; } ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int /*<<< orphan*/  apr_hash_t ;

/* Variables and functions */
 scalar_t__ SVN_INVALID_REVNUM ; 
 scalar_t__ SVN_IS_VALID_REVNUM (scalar_t__) ; 
 int /*<<< orphan*/  SVN_REPOS_DUMPFILE_REVISION_NUMBER ; 
 scalar_t__ SVN_STR_TO_REV (char const*) ; 
 int /*<<< orphan*/  apr_array_make (int /*<<< orphan*/ *,int,int) ; 
 struct revision_baton* apr_pcalloc (int /*<<< orphan*/ *,int) ; 
 char* svn_hash_gets (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct revision_baton *
make_revision_baton(apr_hash_t *headers,
                    struct parse_baton *pb,
                    apr_pool_t *pool)
{
  struct revision_baton *rb = apr_pcalloc(pool, sizeof(*rb));
  const char *val;

  rb->pb = pb;
  rb->pool = pool;
  rb->rev = SVN_INVALID_REVNUM;
  rb->revprops = apr_array_make(rb->pool, 8, sizeof(svn_prop_t));

  if ((val = svn_hash_gets(headers, SVN_REPOS_DUMPFILE_REVISION_NUMBER)))
    {
      rb->rev = SVN_STR_TO_REV(val);

      /* If we're filtering revisions, is this one we'll skip? */
      rb->skipped = (SVN_IS_VALID_REVNUM(pb->start_rev)
                     && ((rb->rev < pb->start_rev) ||
                         (rb->rev > pb->end_rev)));
    }

  return rb;
}