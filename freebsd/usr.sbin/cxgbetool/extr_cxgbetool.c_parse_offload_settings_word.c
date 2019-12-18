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
struct offload_settings {int offload; int rx_coalesce; int tstamp; int sack; int nagle; int ecn; int ddp; int tls; int cong_algo; long sched_class; long txq; long rxq; long mss; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int EINVAL ; 
 char* str_to_number (char*,long*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strsep (char**,char const*) ; 
 int /*<<< orphan*/  warnx (char*,char const*,...) ; 

__attribute__((used)) static int
parse_offload_settings_word(const char *s, char **pnext, const char *ws,
    int *pneg, struct offload_settings *os)
{

	while (*s == '!') {
		(*pneg)++;
		s++;
	}

	if (!strcmp(s, "not")) {
		(*pneg)++;
		return (0);
	}

	if (!strcmp(s, "offload")) {
		os->offload = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s , "coalesce")) {
		os->rx_coalesce = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "timestamp") || !strcmp(s, "tstamp")) {
		os->tstamp = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "sack")) {
		os->sack = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "nagle")) {
		os->nagle = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "ecn")) {
		os->ecn = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "ddp")) {
		os->ddp = (*pneg + 1) & 1;
		*pneg = 0;
	} else if (!strcmp(s, "tls")) {
		os->tls = (*pneg + 1) & 1;
		*pneg = 0;
	} else {
		char *param, *p;
		long val;

		/* Settings with additional parameter handled here. */

		if (*pneg) {
			warnx("\"%s\" is not a valid keyword, or it does not "
			    "support negation.", s);
			return (EINVAL);
		}

		while ((param = strsep(pnext, ws)) != NULL) {
			if (*param != '\0')
				break;
		}
		if (param == NULL) {
			warnx("\"%s\" is not a valid keyword, or it requires a "
			    "parameter that has not been provided.", s);
			return (EINVAL);
		}

		if (!strcmp(s, "cong")) {
			if (!strcmp(param, "reno"))
				os->cong_algo = 0;
			else if (!strcmp(param, "tahoe"))
				os->cong_algo = 1;
			else if (!strcmp(param, "newreno"))
				os->cong_algo = 2;
			else if (!strcmp(param, "highspeed"))
				os->cong_algo = 3;
			else {
				warnx("unknown congestion algorithm \"%s\".", s);
				return (EINVAL);
			}
		} else if (!strcmp(s, "class")) {
			val = -1;
			p = str_to_number(param, &val, NULL);
			/* (nsched_cls - 1) is spelled 15 here. */
			if (*p || val < 0 || val > 15) {
				warnx("invalid scheduling class \"%s\".  "
				    "\"class\" needs an integer value where "
				    "0 <= value <= 15", param);
				return (EINVAL);
			}
			os->sched_class = val;
		} else if (!strcmp(s, "bind") || !strcmp(s, "txq") ||
		    !strcmp(s, "rxq")) {
			val = -1;
			if (strcmp(param, "random")) {
				p = str_to_number(param, &val, NULL);
				if (*p || val < 0 || val > 0xffff) {
					warnx("invalid queue specification "
					    "\"%s\".  \"%s\" needs an integer"
					    " value, or \"random\".",
					    param, s);
					return (EINVAL);
				}
			}
			if (!strcmp(s, "bind")) {
				os->txq = val;
				os->rxq = val;
			} else if (!strcmp(s, "txq")) {
				os->txq = val;
			} else if (!strcmp(s, "rxq")) {
				os->rxq = val;
			} else {
				return (EDOOFUS);
			}
		} else if (!strcmp(s, "mss")) {
			val = -1;
			p = str_to_number(param, &val, NULL);
			if (*p || val <= 0) {
				warnx("invalid MSS specification \"%s\".  "
				    "\"mss\" needs a positive integer value",
				    param);
				return (EINVAL);
			}
			os->mss = val;
		} else  {
			warnx("unknown settings keyword: \"%s\"", s);
			return (EINVAL);
		}
	}

	return (0);
}