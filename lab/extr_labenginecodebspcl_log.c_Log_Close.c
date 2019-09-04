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
struct TYPE_2__ {char* filename; int /*<<< orphan*/ * fp; } ;

/* Variables and functions */
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 TYPE_1__ logfile ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void Log_Close(void)
{
	if (!logfile.fp)
	{
		printf("no log file to close\n");
		return;
	} //end if
	if (fclose(logfile.fp))
	{
		printf("can't close log file %s\n", logfile.filename);
		return;
	} //end if
	logfile.fp = NULL;
	printf("Closed log %s\n", logfile.filename);
}