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
struct console {int dummy; } ;

/* Variables and functions */
 struct console* userboot_comconsp ; 

__attribute__((used)) static void
userboot_comcons_probe(struct console *cp)
{

	/*
	 * Save the console pointer so the comcons_init routine
	 * can set the C_PRESENT* flags. They are not set
	 * here to allow the existing userboot console to
	 * be elected the default.
	 */
	userboot_comconsp = cp;
}