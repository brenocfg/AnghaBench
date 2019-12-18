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
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
typedef  int /*<<< orphan*/  bhnd_nvram_prop ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_DYNAMIC ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/ * bhnd_nvram_prop_new (char const*,int /*<<< orphan*/ *) ; 
 int bhnd_nvram_val_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_val_release (int /*<<< orphan*/ *) ; 

bhnd_nvram_prop *
bhnd_nvram_prop_bytes_new(const char *name, const void *inp, size_t ilen,
    bhnd_nvram_type itype)
{
	bhnd_nvram_prop	*prop;
	bhnd_nvram_val	*val;
	int		 error;

	/* Construct new value instance */
	error = bhnd_nvram_val_new(&val, NULL, inp, ilen, itype,
	    BHND_NVRAM_VAL_DYNAMIC);
	if (error) {
		if (error != ENOMEM) {
			BHND_NV_LOG("invalid input data; initialization "
			    "failed: %d\n", error);
		}

		return (NULL);
	}

	/* Delegate to default implementation */
	prop = bhnd_nvram_prop_new(name, val);

	/* Clean up */
	bhnd_nvram_val_release(val);
	return (prop);
}