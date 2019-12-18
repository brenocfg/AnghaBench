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
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  scalar_t__ svn_boolean_t ;
typedef  scalar_t__ apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/ * MAKE_ERR_BAD_RELATIVE_PATH (char const*,char const*) ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 char* apr_psprintf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svn_dirent_get_longest_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_is_child (char const*,char const*,int /*<<< orphan*/ *) ; 
 char* svn_dirent_join (char const*,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_path_is_url (char const*) ; 
 int /*<<< orphan*/  svn_uri_get_longest_ancestor (char const*,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static svn_error_t *
adjust_paths_for_diff_labels(const char **index_path,
                             const char **orig_path_1,
                             const char **orig_path_2,
                             const char *relative_to_dir,
                             const char *anchor,
                             apr_pool_t *result_pool,
                             apr_pool_t *scratch_pool)
{
  const char *new_path = *index_path;
  const char *new_path1 = *orig_path_1;
  const char *new_path2 = *orig_path_2;

  if (anchor)
    new_path = svn_dirent_join(anchor, new_path, result_pool);

  if (relative_to_dir)
    {
      /* Possibly adjust the paths shown in the output (see issue #2723). */
      const char *child_path = svn_dirent_is_child(relative_to_dir, new_path,
                                                   result_pool);

      if (child_path)
        new_path = child_path;
      else if (! strcmp(relative_to_dir, new_path))
        new_path = ".";
      else
        return MAKE_ERR_BAD_RELATIVE_PATH(new_path, relative_to_dir);
    }

  {
    apr_size_t len;
    svn_boolean_t is_url1;
    svn_boolean_t is_url2;
    /* ### Holy cow.  Due to anchor/target weirdness, we can't
       simply join dwi->orig_path_1 with path, ditto for
       orig_path_2.  That will work when they're directory URLs, but
       not for file URLs.  Nor can we just use anchor1 and anchor2
       from do_diff(), at least not without some more logic here.
       What a nightmare.

       For now, to distinguish the two paths, we'll just put the
       unique portions of the original targets in parentheses after
       the received path, with ellipses for handwaving.  This makes
       the labels a bit clumsy, but at least distinctive.  Better
       solutions are possible, they'll just take more thought. */

    /* ### BH: We can now just construct the repos_relpath, etc. as the
           anchor is available. See also make_repos_relpath() */

    is_url1 = svn_path_is_url(new_path1);
    is_url2 = svn_path_is_url(new_path2);

    if (is_url1 && is_url2)
      len = strlen(svn_uri_get_longest_ancestor(new_path1, new_path2,
                                                scratch_pool));
    else if (!is_url1 && !is_url2)
      len = strlen(svn_dirent_get_longest_ancestor(new_path1, new_path2,
                                                   scratch_pool));
    else
      len = 0; /* Path and URL */

    new_path1 += len;
    new_path2 += len;
  }

  /* ### Should diff labels print paths in local style?  Is there
     already a standard for this?  In any case, this code depends on
     a particular style, so not calling svn_dirent_local_style() on the
     paths below.*/

  if (new_path[0] == '\0')
    new_path = ".";

  if (new_path1[0] == '\0')
    new_path1 = new_path;
  else if (svn_path_is_url(new_path1))
    new_path1 = apr_psprintf(result_pool, "%s\t(%s)", new_path, new_path1);
  else if (new_path1[0] == '/')
    new_path1 = apr_psprintf(result_pool, "%s\t(...%s)", new_path, new_path1);
  else
    new_path1 = apr_psprintf(result_pool, "%s\t(.../%s)", new_path, new_path1);

  if (new_path2[0] == '\0')
    new_path2 = new_path;
  else if (svn_path_is_url(new_path2))
    new_path2 = apr_psprintf(result_pool, "%s\t(%s)", new_path, new_path2);
  else if (new_path2[0] == '/')
    new_path2 = apr_psprintf(result_pool, "%s\t(...%s)", new_path, new_path2);
  else
    new_path2 = apr_psprintf(result_pool, "%s\t(.../%s)", new_path, new_path2);

  *index_path = new_path;
  *orig_path_1 = new_path1;
  *orig_path_2 = new_path2;

  return SVN_NO_ERROR;
}