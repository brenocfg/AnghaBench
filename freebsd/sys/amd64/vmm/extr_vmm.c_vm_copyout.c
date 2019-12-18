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
struct vm_copyinfo {scalar_t__ len; int /*<<< orphan*/  hva; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcopy (char const*,int /*<<< orphan*/ ,scalar_t__) ; 

void
vm_copyout(struct vm *vm, int vcpuid, const void *kaddr,
    struct vm_copyinfo *copyinfo, size_t len)
{
	const char *src;
	int idx;

	src = kaddr;
	idx = 0;
	while (len > 0) {
		bcopy(src, copyinfo[idx].hva, copyinfo[idx].len);
		len -= copyinfo[idx].len;
		src += copyinfo[idx].len;
		idx++;
	}
}