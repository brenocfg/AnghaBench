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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  xo_error (char*) ; 
 int /*<<< orphan*/  xo_finish () ; 

__attribute__((used)) static void
usage(int wcmd)
{
	if (wcmd)
		xo_error("usage: w [-dhin] [-M core] [-N system] [user ...]\n");
	else
		xo_error("usage: uptime\n");
	xo_finish();
	exit(1);
}