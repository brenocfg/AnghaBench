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
 int /*<<< orphan*/  __cpu_simple_unlock (int /*<<< orphan*/ *) ; 
 int handled ; 
 int /*<<< orphan*/  lk ; 

__attribute__((used)) static void
handler(int sig)
{
	handled = 1;
	__cpu_simple_unlock(&lk);
}