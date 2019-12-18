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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;

/* Variables and functions */
 scalar_t__ isdigit (unsigned char) ; 

int
sldns_parse_escape(uint8_t *ch_p, const char** str_p)
{
	uint16_t val;

	if ((*str_p)[0] && isdigit((unsigned char)(*str_p)[0]) &&
	    (*str_p)[1] && isdigit((unsigned char)(*str_p)[1]) &&
	    (*str_p)[2] && isdigit((unsigned char)(*str_p)[2])) {

		val = (uint16_t)(((*str_p)[0] - '0') * 100 +
				 ((*str_p)[1] - '0') *  10 +
				 ((*str_p)[2] - '0'));

		if (val > 255) {
			goto error;
		}
		*ch_p = (uint8_t)val;
		*str_p += 3;
		return 1;

	} else if ((*str_p)[0] && !isdigit((unsigned char)(*str_p)[0])) {

		*ch_p = (uint8_t)*(*str_p)++;
		return 1;
	}
error:
	*str_p = NULL;
	return 0; /* LDNS_WIREPARSE_ERR_SYNTAX_BAD_ESCAPE */
}