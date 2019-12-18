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
 char* BSDAR_VERSION ; 
 int /*<<< orphan*/  EX_OK ; 
 char* archive_version_string () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
ranlib_version(void)
{
	(void)printf("ranlib %s - %s\n", BSDAR_VERSION, archive_version_string());
	exit(EX_OK);
}