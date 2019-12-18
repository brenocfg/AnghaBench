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
typedef  int svn_boolean_t ;
struct node_baton {int dir_depth; scalar_t__ filtered; } ;
struct edit_baton {int requested_depth; scalar_t__ has_target; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  SVN_ERR_MALFUNCTION_NO_RETURN () ; 
#define  svn_depth_empty 133 
#define  svn_depth_exclude 132 
#define  svn_depth_files 131 
#define  svn_depth_immediates 130 
#define  svn_depth_infinity 129 
#define  svn_depth_unknown 128 
 int /*<<< orphan*/  svn_node_file ; 

__attribute__((used)) static svn_boolean_t
okay_to_edit(struct edit_baton *eb,
             struct node_baton *pb,
             svn_node_kind_t kind)
{
  int effective_depth;

  /* If we've already filter out the parent directory, we necessarily
     are filtering out its children, too.  */
  if (pb->filtered)
    return FALSE;

  /* Calculate the effective depth of the parent directory.

     NOTE:  "Depth" in this sense is not the same as the Subversion
     magic depth keywords.  Here, we're talking about a literal,
     integral, stacked depth of directories.

     The root of the edit is generally depth=1, subdirectories thereof
     depth=2, and so on.  But if we have an edit target -- which means
     that the real target of the edit operation isn't the root
     directory, but is instead some immediate child thereof -- we have
     to adjust our calculated effected depth such that the target
     itself is depth=1 (as are its siblings, which we trust aren't
     present in the edit at all), immediate subdirectories thereof are
     depth=2, and so on.
  */
  effective_depth = pb->dir_depth - (eb->has_target ? 1 : 0);
  switch (eb->requested_depth)
    {
    case svn_depth_empty:
      return (effective_depth <= 0);
    case svn_depth_files:
      return ((effective_depth <= 0)
              || (kind == svn_node_file && effective_depth == 1));
    case svn_depth_immediates:
      return (effective_depth <= 1);
    case svn_depth_unknown:
    case svn_depth_exclude:
    case svn_depth_infinity:
      /* Shouldn't reach; see svn_delta_depth_filter_editor() */
    default:
      SVN_ERR_MALFUNCTION_NO_RETURN();
    }
}