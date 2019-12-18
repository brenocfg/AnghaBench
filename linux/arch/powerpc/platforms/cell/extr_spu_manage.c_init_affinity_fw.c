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

/* Variables and functions */
 int MAX_NUMNODES ; 
 int /*<<< orphan*/  init_affinity_node (int) ; 

__attribute__((used)) static void init_affinity_fw(void)
{
	int cbe;

	for (cbe = 0; cbe < MAX_NUMNODES; cbe++)
		init_affinity_node(cbe);
}