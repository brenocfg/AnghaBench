#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  el_outfile; } ;
typedef  TYPE_1__ EditLine ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terminal_mutex ; 
 int /*<<< orphan*/  terminal_outfile ; 
 int /*<<< orphan*/  terminal_putc ; 
 int /*<<< orphan*/  tputs (char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
terminal_tputs(EditLine *el, const char *cap, int affcnt)
{
#ifdef _REENTRANT
	pthread_mutex_lock(&terminal_mutex);
#endif
	terminal_outfile = el->el_outfile;
	(void)tputs(cap, affcnt, terminal_putc);
#ifdef _REENTRANT
	pthread_mutex_unlock(&terminal_mutex);
#endif
}