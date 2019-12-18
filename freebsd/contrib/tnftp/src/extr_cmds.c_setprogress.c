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
 int /*<<< orphan*/  code ; 
 scalar_t__ hash ; 
 scalar_t__ progress ; 
 int /*<<< orphan*/  togglevar (int,char**,scalar_t__*,char*) ; 

void
setprogress(int argc, char *argv[])
{

	code = togglevar(argc, argv, &progress, "Progress bar");
	if (progress)
		hash = 0;
}