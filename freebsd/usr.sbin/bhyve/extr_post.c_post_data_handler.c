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
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
post_data_handler(struct vmctx *ctx, int vcpu, int in, int port, int bytes,
		  uint32_t *eax, void *arg)
{
	assert(in == 1);

	if (bytes != 1)
		return (-1);

	*eax = 0xff;		/* return some garbage */
	return (0);
}