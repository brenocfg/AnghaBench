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
 int /*<<< orphan*/  ofw_dump_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char const*,int,int) ; 
 int /*<<< orphan*/  ofw_finddevice (int,char const*) ; 
 int /*<<< orphan*/  ofw_root (int) ; 

__attribute__((used)) static void
ofw_dump(int fd, const char *start, int rec, int prop, const char *pmatch,
    int raw, int str)
{
	phandle_t n;

	n = start == NULL ? ofw_root(fd) : ofw_finddevice(fd, start);
	ofw_dump_node(fd, n, 0, rec, prop, pmatch, raw, str);
}