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

/* Variables and functions */
 int EOF ; 
 int badopt (char*,char) ; 
 char* ntp_optarg ; 
 int ntp_optind ; 
 char ntp_optopt ; 
 char* prog ; 
 char* scan ; 

int
ntp_getopt(
	int argc,
	char *argv[],
	const char *optstring
	)
{
	register char c;
	register const char *place;

	prog = argv[0];
	ntp_optarg = NULL;

	if (ntp_optind == 0) {
		scan = NULL;
		ntp_optind++;
	}
	
	if (scan == NULL || *scan == '\0') {
		if (ntp_optind >= argc
		    || argv[ntp_optind][0] != '-'
		    || argv[ntp_optind][1] == '\0') {
			return (EOF);
		}
		if (argv[ntp_optind][1] == '-'
		    && argv[ntp_optind][2] == '\0') {
			ntp_optind++;
			return (EOF);
		}
	
		scan = argv[ntp_optind++]+1;
	}

	c = *scan++;
	ntp_optopt = c & 0377;
	for (place = optstring; place != NULL && *place != '\0'; ++place)
	    if (*place == c)
		break;

	if (place == NULL || *place == '\0' || c == ':' || c == '?') {
		return (badopt(": unknown option -", c));
	}

	place++;
	if (*place == ':') {
		if (*scan != '\0') {
			ntp_optarg = scan;
			scan = NULL;
		} else if (ntp_optind >= argc) {
			return (badopt(": option requires argument -", c));
		} else {
			ntp_optarg = argv[ntp_optind++];
		}
	}

	return (c & 0377);
}