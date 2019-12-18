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
 int check_arg_count (int,int) ; 
 int /*<<< orphan*/  color_content (short,short*,short*,short*) ; 
 int /*<<< orphan*/  report_count (int) ; 
 int /*<<< orphan*/  report_error (char*) ; 
 int /*<<< orphan*/  report_int (short) ; 
 int /*<<< orphan*/  report_return (int /*<<< orphan*/ ) ; 
 scalar_t__ sscanf (char*,char*,short*) ; 

void
cmd_color_content(int nargs, char **args)
{
	short colour, red, green, blue;

	if (check_arg_count(nargs, 1) == 1)
		return;

	if (sscanf(args[0], "%hd", &colour) == 0) {
		report_count(1);
		report_error("BAD ARGUMENT");
		return;
	}

	/* XXX - call4 */
	report_count(4);
	report_return(color_content(colour, &red, &green, &blue));
	report_int(red);
	report_int(green);
	report_int(blue);
}