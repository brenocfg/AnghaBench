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
struct netmap_bdg_ops {int (* bwrap_attach ) (char const*,struct netmap_adapter*) ;} ;
struct netmap_adapter {int dummy; } ;

/* Variables and functions */
 int stub1 (char const*,struct netmap_adapter*) ; 

int
netmap_bwrap_attach(const char *nr_name, struct netmap_adapter *hwna,
		struct netmap_bdg_ops *ops)
{
	return ops->bwrap_attach(nr_name, hwna);
}