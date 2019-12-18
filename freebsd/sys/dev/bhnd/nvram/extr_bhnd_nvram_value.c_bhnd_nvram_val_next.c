#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* fmt; } ;
typedef  TYPE_2__ bhnd_nvram_val ;
struct TYPE_6__ {void const* (* op_next ) (TYPE_2__*,void const*,size_t*) ;} ;

/* Variables and functions */
 void const* bhnd_nvram_val_generic_next (TYPE_2__*,void const*,size_t*) ; 
 void const* stub1 (TYPE_2__*,void const*,size_t*) ; 

const void *
bhnd_nvram_val_next(bhnd_nvram_val *value, const void *prev, size_t *olen)
{
	/* Prefer the format implementation */
	if (value->fmt->op_next != NULL)
		return (value->fmt->op_next(value, prev, olen));

	return (bhnd_nvram_val_generic_next(value, prev, olen));
}