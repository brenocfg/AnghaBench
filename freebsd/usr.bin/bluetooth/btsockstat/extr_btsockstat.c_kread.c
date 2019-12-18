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
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_geterr (int /*<<< orphan*/ *) ; 
 int kvm_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
kread(kvm_t *kvmd, u_long addr, char *buffer, int size)
{
	if (kvmd == NULL || buffer == NULL)
		return (-1);

	if (kvm_read(kvmd, addr, buffer, size) != size) {
		warnx("kvm_read: %s", kvm_geterr(kvmd));
		return (-1);
	}

	return (0);
}