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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int btodb (int) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 

uint64_t
cvtblkval(uint64_t limit, char units, const char *itemname)
{

	switch(units) {
	case 'B':
	case 'b':
		limit = btodb(limit);
		break;
	case '\0':	/* historic behavior */
	case ',':	/* historic behavior */
	case ')':	/* historic behavior */
	case 'K':
	case 'k':
		limit *= btodb(1024);
		break;
	case 'M':
	case 'm':
		limit *= btodb(1048576);
		break;
	case 'G':
	case 'g':
		limit *= btodb(1073741824);
		break;
	case 'T':
	case 't':
		limit *= btodb(1099511627776);
		break;
	case 'P':
	case 'p':
		limit *= btodb(1125899906842624);
		break;
	case 'E':
	case 'e':
		limit *= btodb(1152921504606846976);
		break;
	case ' ':
		errx(2, "No space permitted between value and units for %s\n",
		    itemname);
		break;
	default:
		errx(2, "%ju%c: unknown units for %s, specify "
		    "none, K, M, G, T, P, or E\n",
		    (uintmax_t)limit, units, itemname);
		break;
	}
	return (limit);
}