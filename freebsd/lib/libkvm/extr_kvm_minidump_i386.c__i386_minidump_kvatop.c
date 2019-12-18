#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_11__ {TYPE_2__* vmst; } ;
typedef  TYPE_3__ kvm_t ;
typedef  int /*<<< orphan*/  kvaddr_t ;
struct TYPE_9__ {scalar_t__ paemode; } ;
struct TYPE_10__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 scalar_t__ ISALIVE (TYPE_3__*) ; 
 int _i386_minidump_vatop (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int _i386_minidump_vatop_pae (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _kvm_err (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
_i386_minidump_kvatop(kvm_t *kd, kvaddr_t va, off_t *pa)
{

	if (ISALIVE(kd)) {
		_kvm_err(kd, 0, "_i386_minidump_kvatop called in live kernel!");
		return (0);
	}
	if (kd->vmst->hdr.paemode)
		return (_i386_minidump_vatop_pae(kd, va, pa));
	else
		return (_i386_minidump_vatop(kd, va, pa));
}