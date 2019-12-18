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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  ival ;
typedef  scalar_t__ bhnd_nvram_type ;
typedef  scalar_t__ bhnd_nvram_bool_t ;

/* Variables and functions */
 scalar_t__ BHND_NVRAM_TYPE_BOOL ; 
#define  BHND_NVRAM_TYPE_NULL 130 
#define  BHND_NVRAM_TYPE_STRING 129 
#define  BHND_NVRAM_TYPE_STRING_ARRAY 128 
 int /*<<< orphan*/  BHND_NVRAM_TYPE_UINT8 ; 
 int /*<<< orphan*/  BHND_NV_ASSERT (int,char*) ; 
 int EFTYPE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  bhnd_nvram_is_int_type (scalar_t__) ; 
 int bhnd_nvram_val_encode_int (int*,int,int /*<<< orphan*/ ,void*,size_t*,scalar_t__) ; 
 int bhnd_nvram_value_nelem (void const*,size_t,scalar_t__,size_t*) ; 
 int /*<<< orphan*/  strcpy (void*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
bhnd_nvram_val_encode_bool(const void *inp, size_t ilen, bhnd_nvram_type itype,
    void *outp, size_t *olen, bhnd_nvram_type otype)
{
	bhnd_nvram_bool_t	bval;
	size_t			limit, nbytes, nelem;
	int			error;

	BHND_NV_ASSERT(itype == BHND_NVRAM_TYPE_BOOL,
	    ("unsupported type: %d", itype));

	/* Determine output byte limit */
	if (outp != NULL)
		limit = *olen;
	else
		limit = 0;

	/* Must be exactly one element in input */
	if ((error = bhnd_nvram_value_nelem(inp, ilen, itype, &nelem)))
		return (error);

	if (nelem != 1)
		return (EFTYPE);

	/* Fetch (and normalize) boolean value */
	bval = (*(const bhnd_nvram_bool_t *)inp != 0) ? true : false;

	/* Write to output */
	switch (otype) {
	case BHND_NVRAM_TYPE_NULL:
		/* False can be directly encoded as a zero-length NULL value */
		if (bval != false)
			return (EFTYPE);

		nbytes = 0;
		break;

	case BHND_NVRAM_TYPE_STRING:
	case BHND_NVRAM_TYPE_STRING_ARRAY: {
		/* Can encode as "true" or "false" */
		const char *str = bval ? "true" : "false";

		nbytes = strlen(str) + 1;
		if (limit > nbytes)
			strcpy(outp, str);

		break;
	}

	default:
		/* If output type is an integer, we can delegate to standard
		 * integer encoding to encode as zero or one. */
		if (bhnd_nvram_is_int_type(otype)) {
			uint8_t	ival = bval ? 1 : 0;

			return (bhnd_nvram_val_encode_int(&ival, sizeof(ival),
			    BHND_NVRAM_TYPE_UINT8, outp, olen, otype));
		}

		/* Otherwise not representable */
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