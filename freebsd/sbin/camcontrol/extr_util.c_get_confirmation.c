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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 

int
get_confirmation(void)
{
	char str[1024];
	int response = -1;

	do {
		fprintf(stdout, "Are you SURE you want to do this? (yes/no) ");
		if (fgets(str, sizeof(str), stdin) != NULL) {
			if (strncasecmp(str, "yes", 3) == 0)
				response = 1;
			else if (strncasecmp(str, "no", 2) == 0)
				response = 0;
			else
				fprintf(stdout,
				    "Please answer \"yes\" or \"no\"\n");
		} else
			response = 0;
	} while (response == -1);
	return (response);
}