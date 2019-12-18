#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* fmt; } ;
typedef  TYPE_2__ bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
struct TYPE_7__ {size_t (* op_nelem ) (TYPE_2__*) ;int /*<<< orphan*/ * op_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_PANIC (char*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  bhnd_nvram_type_name (int /*<<< orphan*/ ) ; 
 void* bhnd_nvram_val_bytes (TYPE_2__*,size_t*,int /*<<< orphan*/ *) ; 
 void* bhnd_nvram_val_next (TYPE_2__*,void const*,size_t*) ; 
 int bhnd_nvram_value_nelem (void const*,size_t,int /*<<< orphan*/ ,size_t*) ; 
 size_t stub1 (TYPE_2__*) ; 

size_t
bhnd_nvram_val_nelem(bhnd_nvram_val *value)
{
	const void	*bytes;
	bhnd_nvram_type	 type;
	size_t		 nelem, len;
	int		 error;

	/* Prefer format implementation */
	if (value->fmt->op_nelem != NULL)
		return (value->fmt->op_nelem(value));

	/*
	 * If a custom op_next() is defined, bhnd_nvram_value_nelem() almost
	 * certainly cannot produce a valid element count; it assumes a standard
	 * data format that may not apply when custom iteration is required.
	 *
	 * Instead, use bhnd_nvram_val_next() to parse the backing data and
	 * produce a total count.
	 */
	if (value->fmt->op_next != NULL) {
		const void *next;

		next = NULL;
		nelem = 0;
		while ((next = bhnd_nvram_val_next(value, next, &len)) != NULL)
			nelem++;

		return (nelem);
	}

	/* Otherwise, compute the standard element count */
	bytes = bhnd_nvram_val_bytes(value, &len, &type);
	if ((error = bhnd_nvram_value_nelem(bytes, len, type, &nelem))) {
		/* Should always succeed */
		BHND_NV_PANIC("error calculating element count for type '%s' "
		    "with length %zu: %d\n", bhnd_nvram_type_name(type), len,
		    error);
	}

	return (nelem);
}