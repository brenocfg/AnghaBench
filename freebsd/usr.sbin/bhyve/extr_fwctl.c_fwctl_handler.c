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
typedef  int uint32_t ;
struct vmctx {int dummy; } ;

/* Variables and functions */
 int fwctl_inb () ; 
 int fwctl_inl () ; 
 int /*<<< orphan*/  fwctl_outl (int) ; 
 int /*<<< orphan*/  fwctl_outw (int) ; 

__attribute__((used)) static int
fwctl_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
    uint32_t *eax, void *arg)
{

	if (in) {
		if (bytes == 1)
			*eax = fwctl_inb();
		else if (bytes == 4)
			*eax = fwctl_inl();
		else
			*eax = 0xffff;
	} else {
		if (bytes == 2)
			fwctl_outw(*eax);
		else if (bytes == 4)
			fwctl_outl(*eax);
	}

	return (0);
}