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
struct tty_entry {int ret; int /*<<< orphan*/  line; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_T ; 
 int /*<<< orphan*/  Flags ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct tty_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Ttys ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 struct tty_entry* malloc (int) ; 
 int /*<<< orphan*/  next ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_tty(const char *line)
{
	struct tty_entry *tp;
	char *rcp;

	Flags |= AC_T;

	if ((tp = malloc(sizeof(*tp))) == NULL)
		errx(1, "malloc failed");
	tp->len = 0;				/* full match */
	tp->ret = 1;				/* do if match */
	if (*line == '!') {			/* don't do if match */
		tp->ret = 0;
		line++;
	}
	strlcpy(tp->line, line, sizeof(tp->line));
	/* Wildcard. */
	if ((rcp = strchr(tp->line, '*')) != NULL) {
		*rcp = '\0';
		/* Match len bytes only. */
		tp->len = strlen(tp->line);
	}
	SLIST_INSERT_HEAD(&Ttys, tp, next);
}