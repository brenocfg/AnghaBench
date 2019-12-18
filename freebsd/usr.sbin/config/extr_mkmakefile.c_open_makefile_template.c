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
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFSIZ ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* machinename ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

FILE *
open_makefile_template(void)
{
	FILE *ifp;
	char line[BUFSIZ];

	snprintf(line, sizeof(line), "../../conf/Makefile.%s", machinename);
	ifp = fopen(line, "r");
	if (ifp == NULL) {
		snprintf(line, sizeof(line), "Makefile.%s", machinename);
		ifp = fopen(line, "r");
	}
	if (ifp == NULL)
		err(1, "%s", line);
	return (ifp);
}