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
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  cninit_finish () ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
configure_final(void *dummy)
{

	cninit_finish(); 

	if (bootverbose)
		printf("Device configuration finished.\n");

	cold = 0;
}