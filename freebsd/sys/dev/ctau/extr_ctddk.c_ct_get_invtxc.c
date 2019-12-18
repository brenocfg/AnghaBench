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
struct TYPE_4__ {int bcr2; } ;

/* Variables and functions */
 int BCR2_INVTXC0 ; 
 int BCR2_INVTXC1 ; 

int ct_get_invtxc (ct_chan_t *c)
{
	return (c->board->bcr2 & (c->num ? BCR2_INVTXC1 : BCR2_INVTXC0)) != 0;
}