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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  t ;
struct TYPE_3__ {int ibe_interp_argcnt; int ibe_interp_length; int /*<<< orphan*/  ibe_interpreter; } ;
typedef  TYPE_1__ imgact_binmisc_entry_t ;

/* Variables and functions */
 int IBE_INTERP_LEN_MAX ; 
 int /*<<< orphan*/  M_BINMISC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
imgact_binmisc_populate_interp(char *str, imgact_binmisc_entry_t *ibe)
{
	uint32_t len = 0, argc = 1;
	char t[IBE_INTERP_LEN_MAX];
	char *sp, *tp;

	memset(t, 0, sizeof(t));

	/*
	 * Normalize interpreter string. Replace white space between args with
	 * single space.
	 */
	sp = str; tp = t;
	while (*sp != '\0') {
		if (*sp == ' ' || *sp == '\t') {
			if (++len >= IBE_INTERP_LEN_MAX)
				break;
			*tp++ = ' ';
			argc++;
			while (*sp == ' ' || *sp == '\t')
				sp++;
			continue;
		} else {
			*tp++ = *sp++;
			len++;
		}
	}
	*tp = '\0';
	len++;

	ibe->ibe_interpreter = malloc(len, M_BINMISC, M_WAITOK|M_ZERO);

	/* Populate all the ibe fields for the interpreter. */
	memcpy(ibe->ibe_interpreter, t, len);
	ibe->ibe_interp_argcnt = argc;
	ibe->ibe_interp_length = len;
}