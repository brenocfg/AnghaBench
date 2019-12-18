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
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  consout_fd ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  oldterm ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cb_exit(void *arg, int v)
{

	tcsetattr(consout_fd, TCSAFLUSH, &oldterm);
	exit(v);
}