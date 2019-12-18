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
 int /*<<< orphan*/  DEFAULT_FLASH_BASE ; 
 int /*<<< orphan*/  DEFAULT_OUTPUT_FILE ; 
 int /*<<< orphan*/  DEFAULT_VERSION ; 
 int /*<<< orphan*/  INFO (char*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAGIC_HEADER ; 
 int /*<<< orphan*/  VERSION ; 

__attribute__((used)) static void usage(const char* progname)
{
	INFO("Version %s\n"
             "Usage: %s [options]\n"
	     "\t-v <version string>\t - firmware version information, default: %s\n"
	     "\t-m <magic>\t\t - firmware magic, default: %s\n"
	     "\t-f <flash base>\t\t - flash base address, default: 0x%08x\n"
	     "\t-o <output file>\t - firmware output file, default: %s\n"
	     "\t-p <name>:<offset>:<len>:<memaddr>:<entry>:<file>\n "
	     "\t\t\t\t - create a partition from <file>\n"
	     "\t-z\t\t\t - set partition offsets to zero\n"
	     "\t-h\t\t\t - this help\n",
	     VERSION, progname, DEFAULT_VERSION, MAGIC_HEADER,
	     DEFAULT_FLASH_BASE, DEFAULT_OUTPUT_FILE);
}