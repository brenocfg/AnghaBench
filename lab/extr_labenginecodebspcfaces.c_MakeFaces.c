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
typedef  int /*<<< orphan*/  node_t ;

/* Variables and functions */
 int /*<<< orphan*/  MakeFaces_r (int /*<<< orphan*/ *) ; 
 scalar_t__ c_merge ; 
 scalar_t__ c_nodefaces ; 
 scalar_t__ c_subdivide ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 

void MakeFaces (node_t *node)
{
	qprintf ("--- MakeFaces ---\n");
	c_merge = 0;
	c_subdivide = 0;
	c_nodefaces = 0;

	MakeFaces_r (node);

	qprintf ("%5i makefaces\n", c_nodefaces);
	qprintf ("%5i merged\n", c_merge);
	qprintf ("%5i subdivided\n", c_subdivide);
}