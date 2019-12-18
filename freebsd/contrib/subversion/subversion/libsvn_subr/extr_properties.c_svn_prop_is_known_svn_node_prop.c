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
typedef  int /*<<< orphan*/  svn_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_known_prop (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  known_node_props ; 

svn_boolean_t
svn_prop_is_known_svn_node_prop(const char *prop_name)
{
  return is_known_prop(prop_name, known_node_props);
}