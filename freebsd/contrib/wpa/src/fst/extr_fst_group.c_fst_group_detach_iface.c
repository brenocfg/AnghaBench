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
struct fst_iface {int /*<<< orphan*/  group_lentry; } ;
struct fst_group {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dl_list_del (int /*<<< orphan*/ *) ; 

void fst_group_detach_iface(struct fst_group *g, struct fst_iface *i)
{
	dl_list_del(&i->group_lentry);
}