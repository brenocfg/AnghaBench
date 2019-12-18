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
typedef  int /*<<< orphan*/  posix_tnode ;
typedef  scalar_t__ VISIT ;

/* Variables and functions */
 scalar_t__ leaf ; 
 int /*<<< orphan*/  n_seen ; 
 scalar_t__ postorder ; 

__attribute__((used)) static void
treewalk(const posix_tnode *node, VISIT v, int level)
{

	if (v == postorder || v == leaf)
		n_seen++;
}