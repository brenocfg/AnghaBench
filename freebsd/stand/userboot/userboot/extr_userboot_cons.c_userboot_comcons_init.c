#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int c_flags; } ;

/* Variables and functions */
 int C_PRESENTIN ; 
 int C_PRESENTOUT ; 
 TYPE_1__* userboot_comconsp ; 

__attribute__((used)) static int
userboot_comcons_init(int arg)
{

	/*
	 * Set the C_PRESENT* flags to allow the comconsole
	 * to be selected as the active console
	 */
	userboot_comconsp->c_flags |= (C_PRESENTIN | C_PRESENTOUT);
	return (0);
}