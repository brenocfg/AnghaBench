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
 int /*<<< orphan*/  MAGICSTR ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rump_sys_write (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void *
dofifow(void *arg)
{
	int fd = (int)(uintptr_t)arg;
	char buf[512];

	printf("writing\n");
	strcpy(buf, MAGICSTR);
	if (rump_sys_write(fd, buf, strlen(buf)+1) != strlen(buf)+1)
		atf_tc_fail_errno("write to fifo");

	return NULL;
}