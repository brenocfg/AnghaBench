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
struct TYPE_3__ {int tn; int te; } ;
typedef  TYPE_1__ ct_chan_t ;

/* Variables and functions */
 int NBUF ; 

int ct_buf_free (ct_chan_t *c)
{
	return (NBUF + c->tn - c->te - 1) % NBUF;
}