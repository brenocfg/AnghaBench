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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
struct TYPE_2__ {int (* op_copy_val ) (struct bhnd_nvram_data*,void*,int /*<<< orphan*/ **) ;} ;

/* Variables and functions */
 int stub1 (struct bhnd_nvram_data*,void*,int /*<<< orphan*/ **) ; 

int
bhnd_nvram_data_copy_val(struct bhnd_nvram_data *nv, void *cookiep,
    bhnd_nvram_val **value)
{
	return (nv->cls->op_copy_val(nv, cookiep, value));
}