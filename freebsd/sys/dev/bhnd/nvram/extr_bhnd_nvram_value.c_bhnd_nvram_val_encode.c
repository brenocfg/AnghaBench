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
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
struct TYPE_6__ {int (* op_encode ) (TYPE_2__*,void*,size_t*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int bhnd_nvram_val_generic_encode (TYPE_2__*,void*,size_t*,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,void*,size_t*,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_val_encode(bhnd_nvram_val *value, void *outp, size_t *olen,
    bhnd_nvram_type otype)
{
	/* Prefer format implementation */
	if (value->fmt->op_encode != NULL)
		return (value->fmt->op_encode(value, outp, olen, otype));

	return (bhnd_nvram_val_generic_encode(value, outp, olen, otype));
}