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
 int /*<<< orphan*/  TELOPT_LOGOUT ; 
 int /*<<< orphan*/  netflush () ; 
 int /*<<< orphan*/  send_do (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
logout(void)
{
	send_do(TELOPT_LOGOUT, 1);
	(void) netflush();
	return 1;
}