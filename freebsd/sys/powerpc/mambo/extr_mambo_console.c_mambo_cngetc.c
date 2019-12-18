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
struct consdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAMBO_CONSOLE_READ ; 
 int /*<<< orphan*/  alt_break_state ; 
 int /*<<< orphan*/  kdb_alt_break (int,int /*<<< orphan*/ *) ; 
 int mambocall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mambo_cngetc(struct consdev *cp)
{
	int ch;

	ch = mambocall(MAMBO_CONSOLE_READ);

	if (ch > 0 && ch < 0xff) {
#if defined(KDB)
		kdb_alt_break(ch, &alt_break_state);
#endif
		return (ch);
	}

	return (-1);
}