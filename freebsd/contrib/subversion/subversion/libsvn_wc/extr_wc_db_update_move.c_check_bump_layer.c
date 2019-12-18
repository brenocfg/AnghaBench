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
typedef  int /*<<< orphan*/  svn_node_kind_t ;
typedef  int /*<<< orphan*/  svn_error_t ;
typedef  int svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION () ; 
 int /*<<< orphan*/ * SVN_NO_ERROR ; 
 int /*<<< orphan*/  TRUE ; 
 int relpath_depth (char const*) ; 
#define  svn_depth_empty 130 
#define  svn_depth_files 129 
#define  svn_depth_immediates 128 
 int svn_depth_infinity ; 
 int /*<<< orphan*/  svn_node_file ; 
 char* svn_relpath_skip_ancestor (char const*,char const*) ; 

__attribute__((used)) static svn_error_t *
check_bump_layer(svn_boolean_t *skip,
                 svn_depth_t *src_depth,
                 const char *bump_root,
                 svn_depth_t bump_depth,
                 const char *src_relpath,
                 svn_node_kind_t src_kind,
                 apr_pool_t *scratch_pool)
{
  const char *relpath;

  *skip = FALSE;
  *src_depth = bump_depth;

  relpath = svn_relpath_skip_ancestor(bump_root, src_relpath);

  if (!relpath)
    *skip = TRUE;

  if (bump_depth == svn_depth_infinity)
    return SVN_NO_ERROR;

  if (relpath && *relpath == '\0')
    return SVN_NO_ERROR;

  switch (bump_depth)
    {
      case svn_depth_empty:
        *skip = TRUE;
        break;

      case svn_depth_files:
        if (src_kind != svn_node_file)
          {
            *skip = TRUE;
            break;
          }
        /* Fallthrough */
      case svn_depth_immediates:
        if (!relpath || relpath_depth(relpath) > 1)
          *skip = TRUE;

        *src_depth = svn_depth_empty;
        break;
      default:
        SVN_ERR_MALFUNCTION();
    }

  return SVN_NO_ERROR;
}