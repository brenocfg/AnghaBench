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
struct tm {int tm_hour; int tm_min; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_wday; } ;

/* Variables and functions */
 scalar_t__ AM ; 
 scalar_t__ DOT ; 
 scalar_t__ EOF ; 
 scalar_t__ MINUS ; 
 int /*<<< orphan*/  NUMBER ; 
 scalar_t__ PLUS ; 
 scalar_t__ PM ; 
 int atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  sc_token ; 
 scalar_t__ sc_tokid ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ token () ; 

__attribute__((used)) static void
tod(struct tm *tm)
{
    int hour, minute = 0;
    int tlen;

    hour = atoi(sc_token);
    tlen = strlen(sc_token);

    /* first pick out the time of day - if it's 4 digits, we assume
     * a HHMM time, otherwise it's HH DOT MM time
     */
    if (token() == DOT) {
	expect(NUMBER);
	minute = atoi(sc_token);
	if (minute > 59)
	    panic("garbled time");
	token();
    }
    else if (tlen == 4) {
	minute = hour%100;
	if (minute > 59)
	    panic("garbled time");
	hour = hour/100;
    }

    /* check if an AM or PM specifier was given
     */
    if (sc_tokid == AM || sc_tokid == PM) {
	if (hour > 12)
	    panic("garbled time");

	if (sc_tokid == PM) {
	    if (hour != 12)	/* 12:xx PM is 12:xx, not 24:xx */
			hour += 12;
	} else {
	    if (hour == 12)	/* 12:xx AM is 00:xx, not 12:xx */
			hour = 0;
	}
	token();
    }
    else if (hour > 23)
	panic("garbled time");

    /* if we specify an absolute time, we don't want to bump the day even
     * if we've gone past that time - but if we're specifying a time plus
     * a relative offset, it's okay to bump things
     */
    if ((sc_tokid == EOF || sc_tokid == PLUS || sc_tokid == MINUS) && 
	tm->tm_hour > hour) {
	tm->tm_mday++;
	tm->tm_wday++;
    }

    tm->tm_hour = hour;
    tm->tm_min = minute;
    if (tm->tm_hour == 24) {
	tm->tm_hour = 0;
	tm->tm_mday++;
    }
}