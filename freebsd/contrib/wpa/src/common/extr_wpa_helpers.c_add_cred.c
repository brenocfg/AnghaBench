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
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int atoi (char*) ; 
 scalar_t__ wpa_command_resp (char const*,char*,char*,int) ; 

int add_cred(const char *ifname)
{
	char res[30];

	if (wpa_command_resp(ifname, "ADD_CRED", res, sizeof(res)) < 0)
		return -1;
	return atoi(res);
}