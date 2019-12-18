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
struct TYPE_3__ {int vtb_tail; int vtb_size; } ;
typedef  TYPE_1__ sc_vtb_t ;

/* Variables and functions */

void
sc_vtb_seek(sc_vtb_t *vtb, int pos)
{
	vtb->vtb_tail = pos%vtb->vtb_size;
}