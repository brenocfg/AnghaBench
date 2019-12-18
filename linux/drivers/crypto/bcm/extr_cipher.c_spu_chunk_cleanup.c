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
struct TYPE_2__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct brcm_message {TYPE_1__ spu; } ;
struct iproc_reqctx_s {struct brcm_message mb_mssg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct brcm_message*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void spu_chunk_cleanup(struct iproc_reqctx_s *rctx)
{
	/* mailbox message used to tx request */
	struct brcm_message *mssg = &rctx->mb_mssg;

	kfree(mssg->spu.src);
	kfree(mssg->spu.dst);
	memset(mssg, 0, sizeof(struct brcm_message));
}