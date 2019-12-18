#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned long rate; } ;
struct TYPE_5__ {int /*<<< orphan*/  board; TYPE_1__ gopt; } ;
typedef  TYPE_2__ ct_chan_t ;

/* Variables and functions */
 int /*<<< orphan*/  ct_setup_g703 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ct_g703_rate (ct_chan_t *c, unsigned long rate)
{
	c->gopt.rate = rate;
	ct_setup_g703 (c->board);
}