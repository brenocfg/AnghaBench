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
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int ofw_nextprop (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 

int
ofw_firstprop(int fd, phandle_t node, char *buf, int buflen)
{

	return (ofw_nextprop(fd, node, NULL, buf, buflen));
}