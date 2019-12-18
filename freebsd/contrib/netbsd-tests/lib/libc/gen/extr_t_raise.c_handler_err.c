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
 size_t __arraycount (int*) ; 
 int fail ; 
 int* sig ; 

__attribute__((used)) static void
handler_err(int signo)
{
	size_t i;

	for (i = 0; i < __arraycount(sig); i++) {

		if (sig[i] == signo) {
			fail = false;
			break;
		}
	}
}