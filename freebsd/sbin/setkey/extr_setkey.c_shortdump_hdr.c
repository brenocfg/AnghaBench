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
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*) ; 

void
shortdump_hdr()
{
	printf("%-4s %-3s %-1s %-8s %-7s %s -> %s\n",
		"time", "p", "s", "spi", "ltime", "src", "dst");
}