#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_4__ {int /*<<< orphan*/  program; int /*<<< orphan*/  pmfd; } ;
typedef  TYPE_1__ kvm_t ;

/* Variables and functions */
 int /*<<< orphan*/  _kvm_syserr (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pread (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_sparc64_read_phys(kvm_t *kd, off_t pos, void *buf, size_t size)
{

	/* XXX This has to be a raw file read, kvm_read is virtual. */
	if (pread(kd->pmfd, buf, size, pos) != (ssize_t)size) {
		_kvm_syserr(kd, kd->program, "_sparc64_read_phys: pread");
		return (0);
	}
	return (1);
}