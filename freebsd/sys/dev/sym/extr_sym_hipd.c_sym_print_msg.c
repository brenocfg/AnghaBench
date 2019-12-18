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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ccb_p ;

/* Variables and functions */
 int /*<<< orphan*/  PRINT_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  sym_show_msg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sym_print_msg (ccb_p cp, char *label, u_char *msg)
{
	PRINT_ADDR(cp);
	if (label)
		printf ("%s: ", label);

	(void) sym_show_msg (msg);
	printf (".\n");
}