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
struct printer {char* printer; } ;

/* Variables and functions */
 int MAXPATHLEN ; 
 int /*<<< orphan*/  SQS_STOPP ; 
 int /*<<< orphan*/  lock_file_name (struct printer*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int set_qstate (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  upstat (struct printer*,char*,int /*<<< orphan*/ ) ; 

void
stop_q(struct printer *pp)
{
	int setres;
	char lf[MAXPATHLEN];

	lock_file_name(pp, lf, sizeof lf);
	printf("%s:\n", pp->printer);

	setres = set_qstate(SQS_STOPP, lf);

	if (setres >= 0)
		upstat(pp, "printing disabled\n", 0);
}