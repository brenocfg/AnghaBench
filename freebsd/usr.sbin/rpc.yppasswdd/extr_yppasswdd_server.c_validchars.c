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
 scalar_t__ iscntrl (char) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  yp_error (char*) ; 

__attribute__((used)) static int
validchars(char *arg)
{
	size_t i;

	for (i = 0; i < strlen(arg); i++) {
		if (iscntrl(arg[i])) {
			yp_error("string contains a control character");
			return(1);
		}
		if (arg[i] == ':') {
			yp_error("string contains a colon");
			return(1);
		}
		/* Be evil: truncate strings with \n in them silently. */
		if (arg[i] == '\n') {
			arg[i] = '\0';
			return(0);
		}
	}
	return(0);
}