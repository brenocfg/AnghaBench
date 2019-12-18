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
struct tty {int dummy; } ;
typedef  int /*<<< orphan*/  scr_stat ;

/* Variables and functions */
 int /*<<< orphan*/ * SC_STAT (struct tty*) ; 
 int /*<<< orphan*/  main_console ; 

__attribute__((used)) static scr_stat *
sc_get_stat(struct tty *tp)
{
	if (tp == NULL)
		return (&main_console);
	return (SC_STAT(tp));
}