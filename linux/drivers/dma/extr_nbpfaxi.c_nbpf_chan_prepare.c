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
struct nbpf_channel {int dmarq_cfg; int flags; int terminal; } ;

/* Variables and functions */
 int NBPF_CHAN_CFG_AM ; 
 int NBPF_CHAN_CFG_HIEN ; 
 int NBPF_CHAN_CFG_LOEN ; 
 int NBPF_CHAN_CFG_LVL ; 
 int NBPF_SLAVE_RQ_HIGH ; 
 int NBPF_SLAVE_RQ_LEVEL ; 
 int NBPF_SLAVE_RQ_LOW ; 

__attribute__((used)) static void nbpf_chan_prepare(struct nbpf_channel *chan)
{
	chan->dmarq_cfg = (chan->flags & NBPF_SLAVE_RQ_HIGH ? NBPF_CHAN_CFG_HIEN : 0) |
		(chan->flags & NBPF_SLAVE_RQ_LOW ? NBPF_CHAN_CFG_LOEN : 0) |
		(chan->flags & NBPF_SLAVE_RQ_LEVEL ?
		 NBPF_CHAN_CFG_LVL | (NBPF_CHAN_CFG_AM & 0x200) : 0) |
		chan->terminal;
}