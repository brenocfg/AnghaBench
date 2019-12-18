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
typedef  scalar_t__ time_t ;
struct tm {scalar_t__ tm_isdst; } ;

/* Variables and functions */
 int MAX_STRING_LENGTH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  abbr (struct tm*) ; 
 scalar_t__ delta (struct tm*,struct tm*) ; 
 struct tm* my_localtime (scalar_t__*) ; 
 int /*<<< orphan*/  show (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static time_t
hunt(char *name, time_t lot, time_t hit)
{
	time_t			t;
	long			diff;
	struct tm		lotm;
	register struct tm *	lotmp;
	struct tm		tm;
	register struct tm *	tmp;
	char			loab[MAX_STRING_LENGTH];

	lotmp = my_localtime(&lot);
	if (lotmp != NULL) {
		lotm = *lotmp;
		(void) strncpy(loab, abbr(&lotm), (sizeof loab) - 1);
	}
	for ( ; ; ) {
		diff = (long) (hit - lot);
		if (diff < 2)
			break;
		t = lot;
		t += diff / 2;
		if (t <= lot)
			++t;
		else if (t >= hit)
			--t;
		tmp = my_localtime(&t);
		if (tmp != NULL)
			tm = *tmp;
		if ((lotmp == NULL || tmp == NULL) ? (lotmp == tmp) :
			(delta(&tm, &lotm) == (t - lot) &&
			tm.tm_isdst == lotm.tm_isdst &&
			strcmp(abbr(&tm), loab) == 0)) {
				lot = t;
				lotm = tm;
				lotmp = tmp;
		} else	hit = t;
	}
	show(name, lot, TRUE);
	show(name, hit, TRUE);
	return hit;
}