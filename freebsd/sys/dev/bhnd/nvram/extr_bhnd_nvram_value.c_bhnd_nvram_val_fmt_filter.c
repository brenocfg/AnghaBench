#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int (* op_filter ) (TYPE_1__ const**,void const*,size_t,scalar_t__) ;scalar_t__ native_type; } ;
typedef  TYPE_1__ bhnd_nvram_val_fmt ;
typedef  scalar_t__ bhnd_nvram_type ;

/* Variables and functions */
 int EFTYPE ; 
 int bhnd_nvram_value_check_aligned (void const*,size_t,scalar_t__) ; 
 int stub1 (TYPE_1__ const**,void const*,size_t,scalar_t__) ; 

__attribute__((used)) static int
bhnd_nvram_val_fmt_filter(const bhnd_nvram_val_fmt **fmt, const void *inp,
    size_t ilen, bhnd_nvram_type itype)
{
	const bhnd_nvram_val_fmt	*ofmt, *nfmt;
	int				 error;

	nfmt = ofmt = *fmt;

	/* Validate alignment */
	if ((error = bhnd_nvram_value_check_aligned(inp, ilen, itype)))
		return (error);

	/* If the format does not provide a filter function, it only supports
	 * direct initialization from its native type */
	if (ofmt->op_filter == NULL) {
		if (itype == ofmt->native_type)
			return (0);

		return (EFTYPE);
	}

	/* Use the filter function to determine whether direct initialization
	 * from itype is permitted */
	error = ofmt->op_filter(&nfmt, inp, ilen, itype);
	if (error)
		return (error);

	/* Retry filter with new format? */
	if (ofmt != nfmt) {
		error = bhnd_nvram_val_fmt_filter(&nfmt, inp, ilen, itype);
		if (error)
			return (error);

		/* Success -- provide delegated format to caller */
		*fmt = nfmt;
	}

	/* Value can be initialized with provided format and input type */
	return (0);
}