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
typedef  int /*<<< orphan*/  RETSIGTYPE ;

/* Variables and functions */
 int /*<<< orphan*/  LONGJMP (int /*<<< orphan*/ ,int) ; 
 scalar_t__ current_output ; 
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 int /*<<< orphan*/  interrupt_buf ; 
 scalar_t__ jump ; 
 int /*<<< orphan*/  putc (char,scalar_t__) ; 
 scalar_t__ stderr ; 
 scalar_t__ stdout ; 

__attribute__((used)) static RETSIGTYPE
abortcmd(
	int sig
	)
{
	if (current_output == stdout)
		(void)fflush(stdout);
	putc('\n', stderr);
	(void)fflush(stderr);
	if (jump) {
		jump = 0;
		LONGJMP(interrupt_buf, 1);
	}
}