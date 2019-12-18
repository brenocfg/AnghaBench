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
struct fadump_crash_info_header {unsigned long elfcorehdr_addr; int /*<<< orphan*/  crashing_cpu; int /*<<< orphan*/  magic_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  FADUMP_CPU_UNKNOWN ; 
 int /*<<< orphan*/  FADUMP_CRASH_INFO_MAGIC ; 
 struct fadump_crash_info_header* __va (unsigned long) ; 
 int /*<<< orphan*/  memset (struct fadump_crash_info_header*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long init_fadump_header(unsigned long addr)
{
	struct fadump_crash_info_header *fdh;

	if (!addr)
		return 0;

	fdh = __va(addr);
	addr += sizeof(struct fadump_crash_info_header);

	memset(fdh, 0, sizeof(struct fadump_crash_info_header));
	fdh->magic_number = FADUMP_CRASH_INFO_MAGIC;
	fdh->elfcorehdr_addr = addr;
	/* We will set the crashing cpu id in crash_fadump() during crash. */
	fdh->crashing_cpu = FADUMP_CPU_UNKNOWN;

	return addr;
}