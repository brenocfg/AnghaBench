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
 int /*<<< orphan*/  DEFAULT_OUTPUT_FILE ; 
 int /*<<< orphan*/  DEFAULT_VERSION ; 
 int /*<<< orphan*/  INFO (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_HEADER ; 
 int /*<<< orphan*/  VERSION ; 

__attribute__((used)) static void usage(const char* progname)
{
	INFO("Version %s\n"
             "Usage: %s [options]\n"
	     "\t-v <version string>\t - firmware version information, default: %s\n"
	     "\t-o <output file>\t - firmware output file, default: %s\n"
	     "\t-m <magic>\t - firmware magic, default: %s\n"
	     "\t-k <kernel file>\t\t - kernel file\n"
	     "\t-r <rootfs file>\t\t - rootfs file\n"
	     "\t-B <board name>\t\t - choose firmware layout for specified board (XS2, XS5, RS, XM)\n"
	     "\t-h\t\t\t - this help\n", VERSION,
	     progname, DEFAULT_VERSION, DEFAULT_OUTPUT_FILE, MAGIC_HEADER);
}