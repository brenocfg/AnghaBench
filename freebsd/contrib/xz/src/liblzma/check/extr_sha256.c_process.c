#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  u32; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
struct TYPE_7__ {TYPE_1__ sha256; } ;
struct TYPE_9__ {TYPE_3__ buffer; TYPE_2__ state; } ;
typedef  TYPE_4__ lzma_check_state ;

/* Variables and functions */
 int /*<<< orphan*/  transform (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process(lzma_check_state *check)
{
	transform(check->state.sha256.state, check->buffer.u32);
	return;
}