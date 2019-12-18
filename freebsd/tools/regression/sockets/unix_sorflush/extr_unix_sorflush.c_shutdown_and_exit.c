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
 int /*<<< orphan*/  SHUT_RD ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
shutdown_and_exit(int s)
{

	if (shutdown(s, SHUT_RD) < 0)
		err(-1, "shutdown_and_exit: shutdown");
	exit(0);
}