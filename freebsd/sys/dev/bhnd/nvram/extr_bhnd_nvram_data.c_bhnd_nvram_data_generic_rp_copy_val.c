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
struct bhnd_nvram_data {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_val_fmt ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int BHND_NVRAM_DATA_CAP_READ_PTR ; 
 int /*<<< orphan*/  BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EINVAL ; 
 int bhnd_nvram_data_caps (struct bhnd_nvram_data*) ; 
 void* bhnd_nvram_data_getvar_ptr_info (struct bhnd_nvram_data*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int bhnd_nvram_val_new (int /*<<< orphan*/ **,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_data_generic_rp_copy_val(struct bhnd_nvram_data *nv,
    void *cookiep, bhnd_nvram_val **value)
{
	const bhnd_nvram_val_fmt	*fmt;
	const void			*vptr;
	bhnd_nvram_type			 vtype;
	size_t				 vlen;

	BHND_NV_ASSERT(bhnd_nvram_data_caps(nv) & BHND_NVRAM_DATA_CAP_READ_PTR,
	    ("instance does not advertise READ_PTR support"));

	/* Fetch variable data and value format*/
	vptr = bhnd_nvram_data_getvar_ptr_info(nv, cookiep, &vlen, &vtype,
	    &fmt);
	if (vptr == NULL)
		return (EINVAL);

	/* Allocate and return the new value instance */
	return (bhnd_nvram_val_new(value, fmt, vptr, vlen, vtype,
	    BHND_NVRAM_VAL_DYNAMIC));
}