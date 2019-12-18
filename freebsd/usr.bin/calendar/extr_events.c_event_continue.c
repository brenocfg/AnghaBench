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
struct event {char* text; } ;

/* Variables and functions */
 int /*<<< orphan*/  asprintf (char**,char*,char*,char*) ; 
 char* convert (char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 

void
event_continue(struct event *e, char *txt)
{
	char *oldtext, *text;

	text = convert(txt);
	oldtext = e->text;
	if (oldtext == NULL)
		errx(1, "event_continue: cannot allocate memory");

	asprintf(&e->text, "%s\n%s", oldtext, text);
	if (e->text == NULL)
		errx(1, "event_continue: cannot allocate memory");
	free(oldtext);
	free(text);

	return;
}