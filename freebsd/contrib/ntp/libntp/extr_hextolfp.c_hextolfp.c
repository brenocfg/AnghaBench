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
typedef  int u_long ;
struct TYPE_3__ {int l_ui; int l_uf; } ;
typedef  TYPE_1__ l_fp ;

/* Variables and functions */
 scalar_t__ isspace (unsigned char) ; 
 char* strchr (char const*,char const) ; 

int
hextolfp(
	const char *str,
	l_fp *lfp
	)
{
	register const char *cp;
	register const char *cpstart;
	register u_long dec_i;
	register u_long dec_f;
	char *ind = NULL;
	static const char *digits = "0123456789abcdefABCDEF";

	dec_i = dec_f = 0;
	cp = str;

	/*
	 * We understand numbers of the form:
	 *
	 * [spaces]8_hex_digits[.]8_hex_digits[spaces|\n|\0]
	 */
	while (isspace((unsigned char)*cp))
	    cp++;
	
	cpstart = cp;
	while (*cp != '\0' && (cp - cpstart) < 8 &&
	       (ind = strchr(digits, *cp)) != NULL) {
		dec_i = dec_i << 4;	/* multiply by 16 */
		dec_i += ((ind - digits) > 15)
			? (u_long)(ind - digits - 6)
			: (u_long)(ind - digits);
		cp++;
	}

	if ((cp - cpstart) < 8 || ind == NULL)
	    return 0;
	if (*cp == '.')
	    cp++;

	cpstart = cp;
	while (*cp != '\0' && (cp - cpstart) < 8 &&
	       (ind = strchr(digits, *cp)) != NULL) {
		dec_f = dec_f << 4;	/* multiply by 16 */
		dec_f += ((ind - digits) > 15)
			? (u_long)(ind - digits - 6)
			: (u_long)(ind - digits);
		cp++;
	}

	if ((cp - cpstart) < 8 || ind == NULL)
	    return 0;
	
	if (*cp != '\0' && !isspace((unsigned char)*cp))
	    return 0;

	lfp->l_ui = dec_i;
	lfp->l_uf = dec_f;
	return 1;
}