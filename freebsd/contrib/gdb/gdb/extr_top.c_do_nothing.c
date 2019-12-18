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

/* Variables and functions */
 int /*<<< orphan*/  signal (int,void (*) (int)) ; 

__attribute__((used)) static void
do_nothing (int signo)
{
  /* Under System V the default disposition of a signal is reinstated after
     the signal is caught and delivered to an application process.  On such
     systems one must restore the replacement signal handler if one wishes
     to continue handling the signal in one's program.  On BSD systems this
     is not needed but it is harmless, and it simplifies the code to just do
     it unconditionally. */
  signal (signo, do_nothing);
}