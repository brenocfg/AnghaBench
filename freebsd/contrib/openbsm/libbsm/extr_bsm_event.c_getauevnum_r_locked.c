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
struct au_event_ent {scalar_t__ ae_number; } ;
typedef  scalar_t__ au_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_EVENT_FILE ; 
 int /*<<< orphan*/  AU_LINE_MAX ; 
 int /*<<< orphan*/ * eventfromstr (int /*<<< orphan*/ ,struct au_event_ent*) ; 
 int /*<<< orphan*/ * fgets (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * fp ; 
 int /*<<< orphan*/  linestr ; 
 int /*<<< orphan*/  setauevent_locked () ; 
 char* strrchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static struct au_event_ent *
getauevnum_r_locked(struct au_event_ent *e, au_event_t event_number)
{
	char *nl;

	/* Rewind to beginning of the file. */
	setauevent_locked();

	if ((fp == NULL) && ((fp = fopen(AUDIT_EVENT_FILE, "r")) == NULL))
		return (NULL);

	while (fgets(linestr, AU_LINE_MAX, fp) != NULL) {
		/* Remove new lines. */
		if ((nl = strrchr(linestr, '\n')) != NULL)
			*nl = '\0';

		if (eventfromstr(linestr, e) != NULL) {
			if (event_number == e->ae_number)
				return (e);
		}
	}

	return (NULL);
}