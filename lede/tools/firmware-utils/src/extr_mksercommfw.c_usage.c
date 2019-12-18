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
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void usage(char* argv[]) {
    printf("Usage: %s <sysupgradefile> <kernel_offset> <HWID> <HWVER> <SWID>\n"
           "All are positional arguments ...	\n"
           "	sysupgradefile:     File with the kernel uimage at 0\n"
           "	kernel_offset:      Offset where the kernel is located (decimal, hex or octal notation)\n"
           "	HWID:               Hardware ID, ASCII\n"
           "	HWVER:              Hardware Version, ASCII\n"
           "	SWID:               Software Version (decimal, hex or octal notation)\n"
           "	\n"
           , argv[0]);
}