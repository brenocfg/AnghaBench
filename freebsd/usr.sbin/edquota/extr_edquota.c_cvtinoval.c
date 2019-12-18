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
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 

uint64_t
cvtinoval(uint64_t limit, char units, const char *itemname)
{

	switch(units) {
	case 'B':
	case 'b':
	case '\0':	/* historic behavior */
	case ',':	/* historic behavior */
	case ')':	/* historic behavior */
		break;
	case 'K':
	case 'k':
		limit *= 1000;
		break;
	case 'M':
	case 'm':
		limit *= 1000000;
		break;
	case 'G':
	case 'g':
		limit *= 1000000000;
		break;
	case 'T':
	case 't':
		limit *= 1000000000000;
		break;
	case 'P':
	case 'p':
		limit *= 1000000000000000;
		break;
	case 'E':
	case 'e':
		limit *= 1000000000000000000;
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