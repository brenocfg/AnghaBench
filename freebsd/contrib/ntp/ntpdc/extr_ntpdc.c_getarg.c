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
typedef  int u_long ;
struct TYPE_4__ {char* string; int type; int uval; int ival; int /*<<< orphan*/  netnum; } ;
typedef  TYPE_1__ arg_v ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  IP_VERSION 132 
#define  NTP_ADD 131 
#define  NTP_INT 130 
#define  NTP_STR 129 
#define  NTP_UINT 128 
 int OPT ; 
 int /*<<< orphan*/  ZERO (TYPE_1__) ; 
 int /*<<< orphan*/  ai_fam_templ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getnetnum (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int
getarg(
	char *str,
	int code,
	arg_v *argp
	)
{
	int isneg;
	char *cp, *np;
	static const char *digits = "0123456789";

	ZERO(*argp);
	argp->string = str;
	argp->type   = code & ~OPT;

	switch (argp->type) {
	    case NTP_STR:
		break;
	    case NTP_ADD:
		if (!strcmp("-6", str)) {
			ai_fam_templ = AF_INET6;
			return -1;
		} else if (!strcmp("-4", str)) {
			ai_fam_templ = AF_INET;
			return -1;
		}
		if (!getnetnum(str, &(argp->netnum), (char *)0, 0)) {
			return 0;
		}
		break;
	    case NTP_INT:
	    case NTP_UINT:
		isneg = 0;
		np = str;
		if (*np == '-') {
			np++;
			isneg = 1;
		}

		argp->uval = 0;
		do {
			cp = strchr(digits, *np);
			if (cp == NULL) {
				(void) fprintf(stderr,
					       "***Illegal integer value %s\n", str);
				return 0;
			}
			argp->uval *= 10;
			argp->uval += (u_long)(cp - digits);
		} while (*(++np) != '\0');

		if (isneg) {
			if ((code & ~OPT) == NTP_UINT) {
				(void) fprintf(stderr,
					       "***Value %s should be unsigned\n", str);
				return 0;
			}
			argp->ival = -argp->ival;
		}
		break;
	    case IP_VERSION:
		if (!strcmp("-6", str))
			argp->ival = 6 ;
		else if (!strcmp("-4", str))
			argp->ival = 4 ;
		else {
			(void) fprintf(stderr,
			    "***Version must be either 4 or 6\n");
			return 0;
		}
		break;
	}

	return 1;
}