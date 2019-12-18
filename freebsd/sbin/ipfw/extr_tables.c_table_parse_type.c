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
typedef  int uint32_t ;

/* Variables and functions */
 int EX_USAGE ; 
#define  IPFW_TABLE_FLOW 128 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int /*<<< orphan*/  fill_flags (int /*<<< orphan*/ ,char*,char**,int*,int*) ; 
 int /*<<< orphan*/  flowtypecmds ; 

int
table_parse_type(uint8_t ttype, char *p, uint8_t *tflags)
{
	uint32_t fset, fclear;
	char *e;

	/* Parse type options */
	switch(ttype) {
	case IPFW_TABLE_FLOW:
		fset = fclear = 0;
		if (fill_flags(flowtypecmds, p, &e, &fset, &fclear) != 0)
			errx(EX_USAGE,
			    "unable to parse flow option %s", e);
		*tflags = fset;
		break;
	default:
		return (EX_USAGE);
	}

	return (0);
}