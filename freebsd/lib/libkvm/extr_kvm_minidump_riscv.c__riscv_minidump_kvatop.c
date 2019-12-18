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
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  kvm_t ;
typedef  int /*<<< orphan*/  kvaddr_t ;

/* Variables and functions */
 scalar_t__ ISALIVE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _kvm_err (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int _riscv_minidump_vatop (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
_riscv_minidump_kvatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{

	if (ISALIVE(kd)) {
		_kvm_err(kd, 0,
		    "_riscv_minidump_kvatop called in live kernel!");
		return (0);
	}
	return (_riscv_minidump_vatop(kd, va, pa));
}