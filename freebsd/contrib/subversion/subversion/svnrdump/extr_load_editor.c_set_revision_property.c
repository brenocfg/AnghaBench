#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  svn_string_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
struct revision_baton {scalar_t__ rev; int rev_offset; int /*<<< orphan*/  const* author; int /*<<< orphan*/  const* datestamp; int /*<<< orphan*/  pool; TYPE_1__* pb; int /*<<< orphan*/  revprop_table; } ;
struct TYPE_2__ {int /*<<< orphan*/  session; int /*<<< orphan*/  skip_revprops; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_AUTHOR ; 
 int /*<<< orphan*/  SVN_PROP_REVISION_DATE ; 
 int /*<<< orphan*/  apr_pstrdup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_hash_gets (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  svn_hash_sets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  svn_ra_change_rev_prop2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos__normalize_prop (int /*<<< orphan*/  const**,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_repos__validate_prop (char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static svn_error_t *
set_revision_property(void *baton,
                      const char *name,
                      const svn_string_t *value)
{
  struct revision_baton *rb = baton;

  SVN_ERR(svn_repos__normalize_prop(&value, NULL, name, value,
                                    rb->pool, rb->pool));
  SVN_ERR(svn_repos__validate_prop(name, value, rb->pool));

  if (rb->rev > 0)
    {
      if (! svn_hash_gets(rb->pb->skip_revprops, name))
        svn_hash_sets(rb->revprop_table,
                      apr_pstrdup(rb->pool, name), value);
    }
  else if (rb->rev_offset == -1
           && ! svn_hash_gets(rb->pb->skip_revprops, name))
    {
      /* Special case: set revision 0 properties directly (which is
         safe because the commit_editor hasn't been created yet), but
         only when loading into an 'empty' filesystem. */
      SVN_ERR(svn_ra_change_rev_prop2(rb->pb->session, 0,
                                      name, NULL, value, rb->pool));
    }

  /* Remember any datestamp/ author that passes through (see comment
     in close_revision). */
  if (!strcmp(name, SVN_PROP_REVISION_DATE))
    rb->datestamp = value;
  if (!strcmp(name, SVN_PROP_REVISION_AUTHOR))
    rb->author = value;

  return SVN_NO_ERROR;
}