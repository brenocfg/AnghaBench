#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_data {TYPE_1__* cls; } ;
struct TYPE_2__ {int (* op_getvar_order ) (struct bhnd_nvram_data*,void*,void*) ;} ;

/* Variables and functions */
 int stub1 (struct bhnd_nvram_data*,void*,void*) ; 

int
bhnd_nvram_data_getvar_order(struct bhnd_nvram_data *nv, void *cookiep1,
    void *cookiep2)
{
	return (nv->cls->op_getvar_order(nv, cookiep1, cookiep2));
}