#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bhnd_nvram_plist ;
struct TYPE_4__ {int (* op_serialize ) (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t*) ;} ;
typedef  TYPE_1__ bhnd_nvram_data_class ;

/* Variables and functions */
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t*) ; 

int
bhnd_nvram_data_serialize(bhnd_nvram_data_class *cls,
    bhnd_nvram_plist *props, bhnd_nvram_plist *options, void *outp,
    size_t *olen)
{
	return (cls->op_serialize(cls, props, options, outp, olen));
}