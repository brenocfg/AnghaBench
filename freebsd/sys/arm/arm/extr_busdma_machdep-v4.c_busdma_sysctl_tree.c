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
struct sysctl_ctx_list {int dummy; } ;
struct bounce_zone {struct sysctl_ctx_list sysctl_tree; } ;

/* Variables and functions */

__attribute__((used)) static struct sysctl_ctx_list *
busdma_sysctl_tree(struct bounce_zone *bz)
{

	return (&bz->sysctl_tree);
}