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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETDEBUG ; 
#define  PF_DEBUG_MISC 131 
#define  PF_DEBUG_NOISY 130 
#define  PF_DEBUG_NONE 129 
#define  PF_DEBUG_URGENT 128 
 int PF_OPT_QUIET ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 

void
pfctl_debug(int dev, u_int32_t level, int opts)
{
	if (ioctl(dev, DIOCSETDEBUG, &level))
		err(1, "DIOCSETDEBUG");
	if ((opts & PF_OPT_QUIET) == 0) {
		fprintf(stderr, "debug level set to '");
		switch (level) {
		case PF_DEBUG_NONE:
			fprintf(stderr, "none");
			break;
		case PF_DEBUG_URGENT:
			fprintf(stderr, "urgent");
			break;
		case PF_DEBUG_MISC:
			fprintf(stderr, "misc");
			break;
		case PF_DEBUG_NOISY:
			fprintf(stderr, "loud");
			break;
		default:
			fprintf(stderr, "<invalid>");
			break;
		}
		fprintf(stderr, "'\n");
	}
}