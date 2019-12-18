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
struct ttyent {int /*<<< orphan*/  ty_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  endttyent () ; 
 struct ttyent* getttyent () ; 
 int /*<<< orphan*/  setttyent () ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

struct ttyent *
getttynam(const char *tty)
{
	struct ttyent *t;

	if (strncmp(tty, "/dev/", 5) == 0)
		tty += 5;
	setttyent();
	while ( (t = getttyent()) )
		if (!strcmp(tty, t->ty_name))
			break;
	endttyent();
	return (t);
}