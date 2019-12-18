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
struct roff_node {scalar_t__ sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MD_sp ; 
 scalar_t__ SEC_SEE_ALSO ; 
 int /*<<< orphan*/  outflags ; 

__attribute__((used)) static int
md_pre_Rs(struct roff_node *n)
{
	if (n->sec == SEC_SEE_ALSO)
		outflags |= MD_sp;
	return 1;
}