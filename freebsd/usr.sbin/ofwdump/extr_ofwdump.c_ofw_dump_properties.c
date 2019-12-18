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
typedef  int /*<<< orphan*/  prop ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ofw_dump_property (int,int /*<<< orphan*/ ,int,char*,int,int) ; 
 int ofw_firstprop (int,int /*<<< orphan*/ ,char*,int) ; 
 int ofw_nextprop (int,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void
ofw_dump_properties(int fd, phandle_t n, int level, int raw, int str)
{
	int nlen;
	char prop[32];

	for (nlen = ofw_firstprop(fd, n, prop, sizeof(prop)); nlen != 0;
	     nlen = ofw_nextprop(fd, n, prop, prop, sizeof(prop)))
		ofw_dump_property(fd, n, level, prop, raw, str);
}