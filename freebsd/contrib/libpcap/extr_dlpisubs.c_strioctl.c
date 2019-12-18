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
struct strioctl {int ic_cmd; int ic_timout; int ic_len; char* ic_dp; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_STR ; 
 int ioctl (int,int /*<<< orphan*/ ,struct strioctl*) ; 

int
strioctl(int fd, int cmd, int len, char *dp)
{
	struct strioctl str;
	int retv;

	str.ic_cmd = cmd;
	str.ic_timout = -1;
	str.ic_len = len;
	str.ic_dp = dp;
	if ((retv = ioctl(fd, I_STR, &str)) < 0)
		return (retv);

	return (str.ic_len);
}