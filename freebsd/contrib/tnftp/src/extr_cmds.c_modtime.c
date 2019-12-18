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
typedef  int time_t ;

/* Variables and functions */
 int /*<<< orphan*/  UPRINTF (char*,char*) ; 
 int /*<<< orphan*/  another (int*,char***,char*) ; 
 int code ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  localtime (int*) ; 
 int remotemodtime (char*,int) ; 
 char* rfc2822time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttyout ; 

void
modtime(int argc, char *argv[])
{
	time_t mtime;

	if (argc == 0 || argc > 2 ||
	    (argc == 1 && !another(&argc, &argv, "remote-file"))) {
		UPRINTF("usage: %s remote-file\n", argv[0]);
		code = -1;
		return;
	}
	mtime = remotemodtime(argv[1], 1);
	if (mtime != -1)
		fprintf(ttyout, "%s\t%s", argv[1],
		    rfc2822time(localtime(&mtime)));
	code = (mtime > 0);
}