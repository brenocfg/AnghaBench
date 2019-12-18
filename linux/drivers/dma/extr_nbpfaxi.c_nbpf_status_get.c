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
typedef  int u32 ;
struct nbpf_channel {TYPE_1__* nbpf; } ;
struct TYPE_2__ {int chan; } ;

/* Variables and functions */
 int BIT (struct nbpf_channel*) ; 
 int /*<<< orphan*/  NBPF_DSTAT_END ; 
 int nbpf_read (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nbpf_status_get(struct nbpf_channel *chan)
{
	u32 status = nbpf_read(chan->nbpf, NBPF_DSTAT_END);

	return status & BIT(chan - chan->nbpf->chan);
}