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
struct ttyent {int ty_status; } ;

/* Variables and functions */
 struct ttyent* getttynam (char const*) ; 

__attribute__((used)) static int
isttystat(const char *tty, int flag)
{
	struct ttyent *t;

	return ((t = getttynam(tty)) == NULL) ? 0 : !!(t->ty_status & flag);
}