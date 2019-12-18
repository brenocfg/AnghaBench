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
typedef  int pf_tcpopts_t ;

/* Variables and functions */
 int PF_OSFP_MAX_OPTS ; 
 int PF_OSFP_TCPOPT_BITS ; 
 int PF_OSFP_TCPOPT_MSS ; 
 int PF_OSFP_TCPOPT_NOP ; 
 int PF_OSFP_TCPOPT_SACK ; 
 int PF_OSFP_TCPOPT_TS ; 
 int PF_OSFP_TCPOPT_WSCALE ; 
 int T_DC ; 
 int T_MOD ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*,int,char const,...) ; 
 int /*<<< orphan*/  isdigit (char const) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int toupper (char const) ; 

int
get_tcpopts(const char *filename, int lineno, const char *tcpopts,
    pf_tcpopts_t *packed, int *optcnt, int *mss, int *mss_mod, int *wscale,
    int *wscale_mod, int *ts0)
{
	int i, opt;

	*packed = 0;
	*optcnt = 0;
	*wscale = 0;
	*wscale_mod = T_DC;
	*mss = 0;
	*mss_mod = T_DC;
	*ts0 = 0;
	if (strcmp(tcpopts, ".") == 0)
		return (0);

	for (i = 0; tcpopts[i] && *optcnt < PF_OSFP_MAX_OPTS;) {
		switch ((opt = toupper(tcpopts[i++]))) {
		case 'N':	/* FALLTHROUGH */
		case 'S':
			*packed = (*packed << PF_OSFP_TCPOPT_BITS) |
			    (opt == 'N' ? PF_OSFP_TCPOPT_NOP :
			    PF_OSFP_TCPOPT_SACK);
			break;
		case 'W':	/* FALLTHROUGH */
		case 'M': {
			int *this_mod, *this;

			if (opt == 'W') {
				this = wscale;
				this_mod = wscale_mod;
			} else {
				this = mss;
				this_mod = mss_mod;
			}
			*this = 0;
			*this_mod = 0;

			*packed = (*packed << PF_OSFP_TCPOPT_BITS) |
			    (opt == 'W' ? PF_OSFP_TCPOPT_WSCALE :
			    PF_OSFP_TCPOPT_MSS);
			if (tcpopts[i] == '*' && (tcpopts[i + 1] == '\0' ||
			    tcpopts[i + 1] == ',')) {
				*this_mod = T_DC;
				i++;
				break;
			}

			if (tcpopts[i] == '%') {
				*this_mod = T_MOD;
				i++;
			}
			do {
				if (!isdigit(tcpopts[i])) {
					fprintf(stderr, "%s:%d unknown "
					    "character '%c' in %c TCP opt\n",
					    filename, lineno, tcpopts[i], opt);
					return (1);
				}
				*this = (*this * 10) + tcpopts[i++] - '0';
			} while(tcpopts[i] != ',' && tcpopts[i] != '\0');
			break;
		}
		case 'T':
			if (tcpopts[i] == '0') {
				*ts0 = 1;
				i++;
			}
			*packed = (*packed << PF_OSFP_TCPOPT_BITS) |
			    PF_OSFP_TCPOPT_TS;
			break;
		}
		(*optcnt) ++;
		if (tcpopts[i] == '\0')
			break;
		if (tcpopts[i] != ',') {
			fprintf(stderr, "%s:%d unknown option to %c TCP opt\n",
			    filename, lineno, opt);
			return (1);
		}
		i++;
	}

	return (0);
}