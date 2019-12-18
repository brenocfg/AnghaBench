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
 char* BCMFW ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static void 
bcmfw_usage(void)
{
	fprintf(stdout,
"Usage: %s -n name -m md_file -f fw_file\n"
"Where:\n" \
"\t-n name              device name\n" \
"\t-m mini-driver       image mini-driver image file name for download\n" \
"\t-f firmware image    firmware image file name for download\n" \
"\t-h                   display this message\n", BCMFW);

	exit(255);
}