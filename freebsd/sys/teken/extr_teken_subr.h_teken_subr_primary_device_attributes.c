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
typedef  int /*<<< orphan*/  teken_t ;

/* Variables and functions */
 int /*<<< orphan*/  teken_funcs_respond (int /*<<< orphan*/  const*,char const*,int) ; 
 int /*<<< orphan*/  teken_printf (char*) ; 

__attribute__((used)) static void
teken_subr_primary_device_attributes(const teken_t *t, unsigned int request)
{

	if (request == 0) {
		const char response[] = "\x1B[?1;2c";

		teken_funcs_respond(t, response, sizeof response - 1);
	} else {
		teken_printf("Unknown DA1\n");
	}
}