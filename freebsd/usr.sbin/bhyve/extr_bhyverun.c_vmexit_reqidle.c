#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmctx {int dummy; } ;
struct vm_exit {scalar_t__ inst_length; } ;
struct TYPE_2__ {int /*<<< orphan*/  vmexit_reqidle; } ;

/* Variables and functions */
 int VMEXIT_CONTINUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ stats ; 

__attribute__((used)) static int
vmexit_reqidle(struct vmctx *ctx, struct vm_exit *vmexit, int *pvcpu)
{

	assert(vmexit->inst_length == 0);

	stats.vmexit_reqidle++;

	return (VMEXIT_CONTINUE);
}