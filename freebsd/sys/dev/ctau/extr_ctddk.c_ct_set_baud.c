#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mode; } ;
typedef  TYPE_1__ ct_chan_t ;

/* Variables and functions */
 scalar_t__ M_E1 ; 
 scalar_t__ M_G703 ; 
 int /*<<< orphan*/  ct_chan_baud (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  ct_g703_rate (TYPE_1__*,unsigned long) ; 

void ct_set_baud (ct_chan_t *c, unsigned long baud)
{
	unsigned long r;

	if (c->mode == M_E1)
		return;
	if (c->mode == M_G703) {
		if	(baud >= 2048000)  r = 2048;
		else if (baud >= 1024000)  r = 1024;
		else if (baud >= 512000)   r = 512;
		else if (baud >= 256000)   r = 256;
		else if (baud >= 128000)   r = 128;
		else			   r = 64;
		ct_g703_rate (c, r);
	} else
		ct_chan_baud (c, baud);
}