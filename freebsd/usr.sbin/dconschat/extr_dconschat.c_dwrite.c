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
struct dcons_state {int flags; int type; int /*<<< orphan*/  kd; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int F_RD_ONLY ; 
#define  TYPE_FW 129 
#define  TYPE_KVM 128 
 int kvm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int pwrite (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dwrite(struct dcons_state *dc, void *buf, size_t n, off_t offset)
{
	if ((dc->flags & F_RD_ONLY) != 0)
		return (n);

	switch (dc->type) {
	case TYPE_FW:
		return (pwrite(dc->fd, buf, n, offset));
	case TYPE_KVM:
		return (kvm_write(dc->kd, offset, buf, n));
	}
	return (-1);
}