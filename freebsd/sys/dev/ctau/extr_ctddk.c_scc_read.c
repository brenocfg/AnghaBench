#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int sccrx_empty; int sccrx_e; size_t sccrx_b; unsigned char* sccrx; } ;
typedef  TYPE_1__ ct_chan_t ;

/* Variables and functions */
 int SCCBUFSZ ; 

int scc_read (ct_chan_t *c, unsigned char *d, int len)
{
	int i, bytes;

	if (c->sccrx_empty)
		bytes = 0;
	else
		bytes = (SCCBUFSZ + c->sccrx_e - 1 - c->sccrx_b) %
				SCCBUFSZ + 1;
	if (len > bytes)
		return -1;

	for (i=0; i<len; i++){
		d[i] = c->sccrx[c->sccrx_b];
		c->sccrx_b = (c->sccrx_b+1) % SCCBUFSZ;
	}
	if (c->sccrx_b==c->sccrx_e)
		c->sccrx_empty = 1;
	return 0;
}