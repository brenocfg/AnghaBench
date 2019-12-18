#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  port; } ;
typedef  TYPE_1__ ct_board_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCR0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_disable_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  ct_led (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ct_setup_board (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ct_close_board (ct_board_t *b)
{
	ct_setup_board (b, 0, 0, 0);

	/* Reset the controller. */
	outb (BCR0(b->port), 0);

	/* Disable DMA channel. */
	ct_disable_dma (b);

	ct_led (b, 0);
}