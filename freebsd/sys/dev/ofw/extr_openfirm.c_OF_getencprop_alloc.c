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
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int OF_getencprop_alloc_multi (int /*<<< orphan*/ ,char const*,int,void**) ; 

ssize_t
OF_getencprop_alloc(phandle_t package, const char *name, void **buf)
{
	ssize_t ret;

	ret = OF_getencprop_alloc_multi(package, name, sizeof(pcell_t),
	    buf);
	if (ret < 0)
		return (ret);
	else
		return (ret * sizeof(pcell_t));
}