#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  vtable; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* out ) (int /*<<< orphan*/ *,unsigned char*) ;} ;

/* Variables and functions */
 TYPE_2__ pcr_ctx ; 
 size_t pcr_hlen ; 
 TYPE_1__* pcr_md ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,unsigned char*) ; 

ssize_t
ve_pcr_get(unsigned char *buf, size_t sz)
{
	if (!pcr_md)
		return (-1);
	if (sz < pcr_hlen)
		return (-1);
	pcr_md->out(&pcr_ctx.vtable, buf);
	return (pcr_hlen);
}