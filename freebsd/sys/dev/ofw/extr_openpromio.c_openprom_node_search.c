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
typedef  int phandle_t ;

/* Variables and functions */
 int EINVAL ; 
 int OF_child (int) ; 
 int OF_peer (int) ; 

__attribute__((used)) static int
openprom_node_search(phandle_t root, phandle_t node)
{
	phandle_t child;

	if (root == node)
		return (0);
	for (child = OF_child(root); child != 0 && child != -1;
	    child = OF_peer(child))
		if (openprom_node_search(child, node) == 0)
			return (0);
	return (EINVAL);
}