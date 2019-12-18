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
struct TYPE_5__ {scalar_t__ num; TYPE_1__* board; } ;
typedef  TYPE_2__ ct_chan_t ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSR1 (int /*<<< orphan*/ ) ; 
 int BSR1_DSR0 ; 
 int BSR1_DSR1 ; 
 int inb (int /*<<< orphan*/ ) ; 

int ct_get_dsr (ct_chan_t *c)
{
	return (inb (BSR1(c->board->port)) &
		(c->num ? BSR1_DSR1 : BSR1_DSR0)) != 0;
}