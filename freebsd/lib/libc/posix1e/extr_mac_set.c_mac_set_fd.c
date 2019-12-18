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
struct mac {int dummy; } ;

/* Variables and functions */
 int __mac_set_fd (int,struct mac*) ; 

int
mac_set_fd(int fd, struct mac *label)
{

	return (__mac_set_fd(fd, label));
}