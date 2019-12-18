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

__attribute__((used)) static int
default_inout(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
              uint32_t *eax, void *arg)
{
	if (in) {
		switch (bytes) {
		case 4:
			*eax = 0xffffffff;
			break;
		case 2:
			*eax = 0xffff;
			break;
		case 1:
			*eax = 0xff;
			break;
		}
	}

	return (0);
}