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
typedef  void u_char ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int /*<<< orphan*/  BHND_NV_LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bhnd_nvram_type_name (int /*<<< orphan*/ ) ; 
 size_t bhnd_nvram_value_size (void const*,size_t,int /*<<< orphan*/ ,int) ; 

const void *
bhnd_nvram_value_array_next(const void *inp, size_t ilen, bhnd_nvram_type itype,
    const void *prev, size_t *olen)
{
	const u_char	*next;
	size_t		 offset;

	/* Handle first element */
	if (prev == NULL) {
		/* Zero-length array? */
		if (ilen == 0)
			return (NULL);

		*olen = bhnd_nvram_value_size(inp, ilen, itype, 1);
		return (inp);
	}

	/* Advance to next element */
	BHND_NV_ASSERT(prev >= (const void *)inp, ("invalid cookiep"));
	next = (const u_char *)prev + *olen;
	offset = (size_t)(next - (const u_char *)inp);

	if (offset >= ilen) {
		/* Hit end of the array */
		return (NULL);
	}

	/* Determine element size */
	*olen = bhnd_nvram_value_size(next, ilen - offset, itype, 1);
	if (ilen - offset < *olen) {
		BHND_NV_LOG("short element of type %s -- misaligned "
		    "representation", bhnd_nvram_type_name(itype));
		return (NULL);
	}

	return (next);
}