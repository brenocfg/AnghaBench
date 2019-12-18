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
typedef  int /*<<< orphan*/  u_int ;
struct amd64_set_pkru {unsigned long len; int flags; int /*<<< orphan*/  keyidx; void* addr; } ;
typedef  int /*<<< orphan*/  a64pkru ;

/* Variables and functions */
 int /*<<< orphan*/  X86_SET_PKRU ; 
 int /*<<< orphan*/  memset (struct amd64_set_pkru*,int /*<<< orphan*/ ,int) ; 
 int sysarch (int /*<<< orphan*/ ,struct amd64_set_pkru*) ; 

int
x86_pkru_protect_range(void *addr, unsigned long len, u_int keyidx, int flags)
{
	struct amd64_set_pkru a64pkru;

	memset(&a64pkru, 0, sizeof(a64pkru));
	a64pkru.addr = addr;
	a64pkru.len = len;
	a64pkru.keyidx = keyidx;
	a64pkru.flags = flags;
	return (sysarch(X86_SET_PKRU, &a64pkru));
}