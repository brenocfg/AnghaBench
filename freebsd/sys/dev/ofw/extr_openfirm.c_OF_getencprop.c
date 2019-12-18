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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  pcell_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  be32toh (int /*<<< orphan*/ ) ; 

ssize_t
OF_getencprop(phandle_t node, const char *propname, pcell_t *buf, size_t len)
{
	ssize_t retval;
	int i;

	KASSERT(len % 4 == 0, ("Need a multiple of 4 bytes"));

	retval = OF_getprop(node, propname, buf, len);
	if (retval <= 0)
		return (retval);

	for (i = 0; i < len/4; i++)
		buf[i] = be32toh(buf[i]);

	return (retval);
}