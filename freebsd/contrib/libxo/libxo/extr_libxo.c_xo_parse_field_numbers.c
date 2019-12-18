#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_3__ {unsigned int xfi_fnum; } ;
typedef  TYPE_1__ xo_field_info_t ;
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  xo_failure (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
xo_parse_field_numbers (xo_handle_t *xop, const char *fmt,
			xo_field_info_t *fields, unsigned num_fields)
{
    xo_field_info_t *xfip;
    unsigned field, fnum;
    uint64_t bits = 0;
    const uint64_t one = 1;	/* Avoid 1ULL */

    for (xfip = fields, field = 0; field < num_fields; xfip++, field++) {
	/* Fields default to 1:1 with natural position */
	if (xfip->xfi_fnum == 0)
	    xfip->xfi_fnum = field + 1;
	else if (xfip->xfi_fnum > num_fields) {
	    xo_failure(xop, "field number exceeds number of fields: '%s'", fmt);
	    return -1;
	}

	fnum = xfip->xfi_fnum - 1; /* Move to zero origin */
	if (fnum < 64) {	/* Only test what fits */
	    if (bits & (one << fnum)) {
		xo_failure(xop, "field number %u reused: '%s'",
			   xfip->xfi_fnum, fmt);
		return -1;
	    }
	    bits |= one << fnum;
	}
    }

    return 0;
}