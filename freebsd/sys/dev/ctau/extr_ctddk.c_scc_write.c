#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int scctx_b; size_t scctx_e; unsigned char* scctx; scalar_t__ scctx_empty; } ;
typedef  TYPE_1__ ct_chan_t ;

/* Variables and functions */
 int SCCBUFSZ ; 
 int /*<<< orphan*/  cte_out2d (TYPE_1__*,unsigned char) ; 

int scc_write (ct_chan_t *c, unsigned char *d, int len)
{
	int i, free;

	/* determining free place in buffer */
	if (c->scctx_empty)
		free = SCCBUFSZ;
	else
		free = (SCCBUFSZ + c->scctx_b - c->scctx_e) % SCCBUFSZ;

	if (len > free)
		return -1;

	for (i=0; i<len; i++){
		c->scctx[c->scctx_e] = d[i];
		c->scctx_e = (c->scctx_e+1) % SCCBUFSZ;
	}
	if (c->scctx_empty && len) {
		cte_out2d (c, c->scctx[c->scctx_b]);
		c->scctx_empty = 0;
	}
	return 0;
}