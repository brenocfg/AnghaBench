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
 int MAX_SIGNO ; 
 int /*<<< orphan*/  assert (int) ; 
 int* signo ; 

__attribute__((used)) static void
handler(int s)
{
	assert(s <= MAX_SIGNO);
	signo[s] = 1;
}