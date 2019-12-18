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
struct xlp_intrsrc {int /*<<< orphan*/  irt; int /*<<< orphan*/  bus_ack_arg; int /*<<< orphan*/  irq; int /*<<< orphan*/  (* bus_ack ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  nlm_pic_ack (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xlp_pic_base ; 

__attribute__((used)) static void
xlp_post_filter(void *source)
{
	struct xlp_intrsrc *src = source;

	if (src->bus_ack)
		src->bus_ack(src->irq, src->bus_ack_arg);
	nlm_pic_ack(xlp_pic_base, src->irt);
}