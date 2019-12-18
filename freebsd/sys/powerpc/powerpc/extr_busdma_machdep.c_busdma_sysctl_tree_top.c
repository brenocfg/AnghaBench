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
struct sysctl_oid {int dummy; } ;
struct bounce_zone {struct sysctl_oid* sysctl_tree_top; } ;

/* Variables and functions */

__attribute__((used)) static struct sysctl_oid *
busdma_sysctl_tree_top(struct bounce_zone *bz)
{
	return (bz->sysctl_tree_top);
}