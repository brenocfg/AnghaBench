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
typedef  int /*<<< orphan*/  u_long ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  kvmd ; 
 scalar_t__ kvmd_init () ; 
 int /*<<< orphan*/  xo_warnx (char*,int /*<<< orphan*/ ) ; 

int
kread(u_long addr, void *buf, size_t size)
{

	if (kvmd_init() < 0)
		return (-1);

	if (!buf)
		return (0);
	if (kvm_read(kvmd, addr, buf, size) != (ssize_t)size) {
		xo_warnx("%s", kvm_geterr(kvmd));
		return (-1);
	}
	return (0);
}