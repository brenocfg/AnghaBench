#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ end; } ;
struct TYPE_4__ {scalar_t__ end; scalar_t__ pos; } ;
struct x86_emulate_ctxt {TYPE_1__ mem_read; TYPE_2__ io_read; int /*<<< orphan*/  rip_relative; int /*<<< orphan*/  modrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void init_decode_cache(struct x86_emulate_ctxt *ctxt)
{
	memset(&ctxt->rip_relative, 0,
	       (void *)&ctxt->modrm - (void *)&ctxt->rip_relative);

	ctxt->io_read.pos = 0;
	ctxt->io_read.end = 0;
	ctxt->mem_read.end = 0;
}