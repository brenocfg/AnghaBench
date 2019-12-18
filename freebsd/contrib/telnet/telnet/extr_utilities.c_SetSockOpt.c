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
 int setsockopt (int,int,int,char*,int) ; 

int
SetSockOpt(int fd, int level, int option, int yesno)
{
    return setsockopt(fd, level, option,
				(char *)&yesno, sizeof yesno);
}