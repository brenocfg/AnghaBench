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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAXCOUNT ; 
 scalar_t__ cal_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  closecal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_print_all (int /*<<< orphan*/ *) ; 
 char** extradata ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * opencalin () ; 
 int /*<<< orphan*/ * opencalout () ; 

void
cal(void)
{
	FILE *fpin;
	FILE *fpout;
	int i;

	for (i = 0; i < MAXCOUNT; i++)
		extradata[i] = (char *)calloc(1, 20);


	if ((fpin = opencalin()) == NULL)
		return;

	if ((fpout = opencalout()) == NULL) {
		fclose(fpin);
		return;
	}

	if (cal_parse(fpin, fpout))
		return;

	event_print_all(fpout);
	closecal(fpout);
}