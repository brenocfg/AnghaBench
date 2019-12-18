#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ kind; } ;
typedef  TYPE_1__ svn_opt_revision_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SVN_ERR_CLIENT_BAD_REVISION ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/ * svn_error_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ svn_opt_revision_base ; 
 scalar_t__ svn_opt_revision_unspecified ; 
 scalar_t__ svn_opt_revision_working ; 
 scalar_t__ svn_path_is_url (char const*) ; 

__attribute__((used)) static svn_error_t *
check_paths(svn_boolean_t *is_repos1,
            svn_boolean_t *is_repos2,
            const char *path_or_url1,
            const char *path_or_url2,
            const svn_opt_revision_t *revision1,
            const svn_opt_revision_t *revision2,
            const svn_opt_revision_t *peg_revision)
{
  svn_boolean_t is_local_rev1, is_local_rev2;

  /* Verify our revision arguments in light of the paths. */
  if ((revision1->kind == svn_opt_revision_unspecified)
      || (revision2->kind == svn_opt_revision_unspecified))
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                            _("Not all required revisions are specified"));

  /* Revisions can be said to be local or remote.
   * BASE and WORKING are local revisions.  */
  is_local_rev1 =
    ((revision1->kind == svn_opt_revision_base)
     || (revision1->kind == svn_opt_revision_working));
  is_local_rev2 =
    ((revision2->kind == svn_opt_revision_base)
     || (revision2->kind == svn_opt_revision_working));

  if (peg_revision->kind != svn_opt_revision_unspecified &&
      is_local_rev1 && is_local_rev2)
    return svn_error_create(SVN_ERR_CLIENT_BAD_REVISION, NULL,
                            _("At least one revision must be something other "
                              "than BASE or WORKING when diffing a URL"));

  /* Working copy paths with non-local revisions get turned into
     URLs.  We don't do that here, though.  We simply record that it
     needs to be done, which is information that helps us choose our
     diff helper function.  */
  *is_repos1 = ! is_local_rev1 || svn_path_is_url(path_or_url1);
  *is_repos2 = ! is_local_rev2 || svn_path_is_url(path_or_url2);

  return SVN_NO_ERROR;
}