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
typedef  scalar_t__ svn_node_kind_t ;
typedef  scalar_t__ svn_depth_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ svn_depth_empty ; 
 scalar_t__ svn_depth_files ; 
 scalar_t__ svn_depth_immediates ; 
 scalar_t__ svn_depth_unknown ; 
 scalar_t__ svn_node_dir ; 
 scalar_t__ svn_node_file ; 

__attribute__((used)) static svn_boolean_t
is_depth_upgrade(svn_depth_t wc_depth,
                 svn_depth_t requested_depth,
                 svn_node_kind_t kind)
{
  if (requested_depth == svn_depth_unknown
      || requested_depth <= wc_depth
      || wc_depth == svn_depth_immediates)
    return FALSE;

  if (kind == svn_node_file
      && wc_depth == svn_depth_files)
    return FALSE;

  if (kind == svn_node_dir
      && wc_depth == svn_depth_empty
      && requested_depth == svn_depth_files)
    return FALSE;

  return TRUE;
}