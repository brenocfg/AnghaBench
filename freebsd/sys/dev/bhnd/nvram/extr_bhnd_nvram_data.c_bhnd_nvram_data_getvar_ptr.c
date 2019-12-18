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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
struct TYPE_2__ {void const* (* op_getvar_ptr ) (struct bhnd_nvram_data*,void*,size_t*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 void const* stub1 (struct bhnd_nvram_data*,void*,size_t*,int /*<<< orphan*/ *) ; 

const void *
bhnd_nvram_data_getvar_ptr(struct bhnd_nvram_data *nv, void *cookiep,
    size_t *len, bhnd_nvram_type *type)
{
	return (nv->cls->op_getvar_ptr(nv, cookiep, len, type));
}