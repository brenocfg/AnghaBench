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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_read2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,size_t) ; 

ssize_t
kvm_read(kvm_t *kd, u_long kva, void *buf, size_t len)
{

	return (kvm_read2(kd, kva, buf, len));
}