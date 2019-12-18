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
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 size_t SSIZE_MAX ; 
 scalar_t__ kvm_read (int /*<<< orphan*/ *,unsigned long,void*,size_t) ; 

int
kvm_read_all(kvm_t *kd, unsigned long addr, void *buf, size_t nbytes)
{
	ssize_t error;

	if (nbytes >= SSIZE_MAX)
		return (0);
	error = kvm_read(kd, addr, buf, nbytes);
	return (error == (ssize_t)(nbytes));
}