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
struct event {int month; int day; int var; int /*<<< orphan*/ * extra; int /*<<< orphan*/ * text; int /*<<< orphan*/ * date; } ;

/* Variables and functions */
 int /*<<< orphan*/  addtodate (struct event*,int,int,int) ; 
 scalar_t__ calloc (int,int) ; 
 void* convert (char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 

struct event *
event_add(int year, int month, int day, char *date, int var, char *txt,
    char *extra)
{
	struct event *e;

	/*
	 * Creating a new event:
	 * - Create a new event
	 * - Copy the machine readable day and month
	 * - Copy the human readable and language specific date
	 * - Copy the text of the event
	 */
	e = (struct event *)calloc(1, sizeof(struct event));
	if (e == NULL)
		errx(1, "event_add: cannot allocate memory");
	e->month = month;
	e->day = day;
	e->var = var;
	e->date = convert(date);
	if (e->date == NULL)
		errx(1, "event_add: cannot allocate memory");
	e->text = convert(txt);
	if (e->text == NULL)
		errx(1, "event_add: cannot allocate memory");
	e->extra = NULL;
	if (extra != NULL && extra[0] != '\0')
		e->extra = convert(extra);
	addtodate(e, year, month, day);
	return (e);
}