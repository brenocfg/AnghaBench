#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  bhnd_nvram_val_storage ;
struct TYPE_6__ {scalar_t__ native_type; } ;
typedef  TYPE_1__ bhnd_nvram_val_fmt ;
typedef  int /*<<< orphan*/  bhnd_nvram_val ;
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_NVRAM_VAL_INITIALIZER (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 void* bhnd_nvram_val_alloc_bytes (int /*<<< orphan*/ *,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_1__* bhnd_nvram_val_default_fmt (scalar_t__) ; 
 int bhnd_nvram_val_fmt_filter (TYPE_1__ const**,void const*,size_t,scalar_t__) ; 
 int bhnd_nvram_val_set (int /*<<< orphan*/ *,void const*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 int bhnd_nvram_value_coerce (void const*,size_t,scalar_t__,void*,size_t*,scalar_t__) ; 

__attribute__((used)) static int
bhnd_nvram_val_init_common(bhnd_nvram_val *value,
    bhnd_nvram_val_storage val_storage, const bhnd_nvram_val_fmt *fmt,
    const void *inp, size_t ilen, bhnd_nvram_type itype, uint32_t flags)
{
	void		*outp;
	bhnd_nvram_type	 otype;
	size_t		 olen;
	int		 error;

	/* If the value format is unspecified, we use the default format
	 * for the input data type */
	if (fmt == NULL)
		fmt = bhnd_nvram_val_default_fmt(itype);

	/* Determine expected data type, and allow the format to delegate to
	 * a new format instance */
	if ((error = bhnd_nvram_val_fmt_filter(&fmt, inp, ilen, itype))) {
		/* Direct initialization from the provided input type is
		 * not supported; alue must be initialized with the format's
		 * native type */
		otype = fmt->native_type;
	} else {
		/* Value can be initialized with provided input type */
		otype = itype;
	}

	/* Initialize value instance */
	*value = BHND_NVRAM_VAL_INITIALIZER(fmt, val_storage);

	/* If input data already in native format, init directly. */
	if (otype == itype) {
		error = bhnd_nvram_val_set(value, inp, ilen, itype, flags);
		if (error)
			return (error);

		return (0);
	}
	
	/* Determine size when encoded in native format */
	error = bhnd_nvram_value_coerce(inp, ilen, itype, NULL, &olen, otype);
	if (error)
		return (error);
	
	/* Fetch reference to (or allocate) an appropriately sized buffer */
	outp = bhnd_nvram_val_alloc_bytes(value, olen, otype, flags);
	if (outp == NULL)
		return (ENOMEM);
	
	/* Perform encode */
	error = bhnd_nvram_value_coerce(inp, ilen, itype, outp, &olen, otype);
	if (error)
		return (error);
	
	return (0);
}