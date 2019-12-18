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
 int errno ; 
 int /*<<< orphan*/  printf (char*,int,int,char const*) ; 

__attribute__((used)) static void
print_rtrn_errno(int rtrnVal, const char *eol)
{
	printf("%d %d%s", rtrnVal, rtrnVal != 0 ? errno : 0, eol);

	return;
}