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
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
#define  BHND_NVRAM_TYPE_NULL 128 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EFTYPE ; 
 int ENOMEM ; 

__attribute__((used)) static int
bhnd_nvram_val_encode_null(const void *inp, size_t ilen, bhnd_nvram_type itype,
    void *outp, size_t *olen, bhnd_nvram_type otype)
{
	size_t	limit, nbytes;

	BHND_NV_ASSERT(itype == BHND_NVRAM_TYPE_NULL,
	    ("unsupported type: %d", itype));

	/* Determine output byte limit */
	if (outp != NULL)
		limit = *olen;
	else
		limit = 0;

	nbytes = 0;

	/* Write to output */
	switch (otype) {
	case BHND_NVRAM_TYPE_NULL:
		/* Can be directly encoded as a zero-length NULL value */
		nbytes = 0;
		break;
	default:
		/* Not representable */
		return (EFTYPE);
	}

	/* Provide required length */
	*olen = nbytes;
	if (limit < *olen) {
		if (outp == NULL)
			return (0);

		return (ENOMEM);
	}

	return (0);
}