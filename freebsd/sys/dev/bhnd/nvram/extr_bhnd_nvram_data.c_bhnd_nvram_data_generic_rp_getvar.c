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
 int /*<<< orphan*/  BHND_NVRAM_VAL_BORROW_DATA ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EINVAL ; 
 int bhnd_nvram_data_caps (struct bhnd_nvram_data*) ; 
 void* bhnd_nvram_data_getvar_ptr_info (struct bhnd_nvram_data*,void*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int bhnd_nvram_val_encode (int /*<<< orphan*/ *,void*,size_t*,int /*<<< orphan*/ ) ; 
 int bhnd_nvram_val_init (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

int
bhnd_nvram_data_generic_rp_getvar(struct bhnd_nvram_data *nv, void *cookiep,
    void *outp, size_t *olen, bhnd_nvram_type otype)
{
	bhnd_nvram_val			 val;
	const bhnd_nvram_val_fmt	*fmt;
	const void			*vptr;
	bhnd_nvram_type			 vtype;
	size_t				 vlen;
	int				 error;

	BHND_NV_ASSERT(bhnd_nvram_data_caps(nv) & BHND_NVRAM_DATA_CAP_READ_PTR,
	    ("instance does not advertise READ_PTR support"));

	/* Fetch variable data and value format*/
	vptr = bhnd_nvram_data_getvar_ptr_info(nv, cookiep, &vlen, &vtype,
	    &fmt);
	if (vptr == NULL)
		return (EINVAL);

	/* Attempt value coercion */
	error = bhnd_nvram_val_init(&val, fmt, vptr, vlen, vtype,
	    BHND_NVRAM_VAL_BORROW_DATA);
	if (error)
		return (error);

	error = bhnd_nvram_val_encode(&val, outp, olen, otype);

	/* Clean up */
	bhnd_nvram_val_release(&val);
	return (error);
}