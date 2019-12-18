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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
SeqDiff(u_long x, u_long y)
{
/* Return the difference between two TCP sequence numbers */

/*
    This function is encapsulated in case there are any unusual
    arithmetic conditions that need to be considered.
*/

	return (ntohl(y) - ntohl(x));
}