#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {char const* string; int ival; int /*<<< orphan*/  uval; int /*<<< orphan*/  netnum; } ;
typedef  TYPE_1__ arg_v ;
struct TYPE_5__ {int /*<<< orphan*/  assid; } ;

/* Variables and functions */
#define  IP_VERSION 132 
#define  NTP_ADD 131 
#define  NTP_INT 130 
#define  NTP_STR 129 
#define  NTP_UINT 128 
 int OPT ; 
 TYPE_3__* assoc_cache ; 
 int /*<<< orphan*/  atoint (char const*,int*) ; 
 int /*<<< orphan*/  atouint (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dogetassoc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getnetnum (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  numassoc ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char const*) ; 

__attribute__((used)) static int
getarg(
	const char *str,
	int code,
	arg_v *argp
	)
{
	u_long ul;

	switch (code & ~OPT) {
	case NTP_STR:
		argp->string = str;
		break;

	case NTP_ADD:
		if (!getnetnum(str, &argp->netnum, NULL, 0))
			return 0;
		break;

	case NTP_UINT:
		if ('&' == str[0]) {
			if (!atouint(&str[1], &ul)) {
				fprintf(stderr,
					"***Association index `%s' invalid/undecodable\n",
					str);
				return 0;
			}
			if (0 == numassoc) {
				dogetassoc(stdout);
				if (0 == numassoc) {
					fprintf(stderr,
						"***No associations found, `%s' unknown\n",
						str);
					return 0;
				}
			}
			ul = min(ul, numassoc);
			argp->uval = assoc_cache[ul - 1].assid;
			break;
		}
		if (!atouint(str, &argp->uval)) {
			fprintf(stderr, "***Illegal unsigned value %s\n",
				str);
			return 0;
		}
		break;

	case NTP_INT:
		if (!atoint(str, &argp->ival)) {
			fprintf(stderr, "***Illegal integer value %s\n",
				str);
			return 0;
		}
		break;

	case IP_VERSION:
		if (!strcmp("-6", str)) {
			argp->ival = 6;
		} else if (!strcmp("-4", str)) {
			argp->ival = 4;
		} else {
			fprintf(stderr, "***Version must be either 4 or 6\n");
			return 0;
		}
		break;
	}

	return 1;
}