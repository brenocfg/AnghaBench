#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * rip_nets; int /*<<< orphan*/  rip_vers; void* rip_cmd; } ;
struct TYPE_12__ {TYPE_1__ rip; } ;
struct TYPE_8__ {int /*<<< orphan*/ * rip_nets; void* rip_cmd; } ;
struct TYPE_11__ {TYPE_2__ rip; } ;
struct TYPE_10__ {TYPE_2__* buf; int /*<<< orphan*/ * base; } ;
struct TYPE_9__ {TYPE_1__* buf; int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 void* RIPCMD_RESPONSE ; 
 int /*<<< orphan*/  RIPv2 ; 
 TYPE_6__ rip_v2_buf ; 
 TYPE_5__ ripv12_buf ; 
 TYPE_4__ v12buf ; 
 TYPE_3__ v2buf ; 

void
bufinit(void)
{
	ripv12_buf.rip.rip_cmd = RIPCMD_RESPONSE;
	v12buf.buf = &ripv12_buf.rip;
	v12buf.base = &v12buf.buf->rip_nets[0];

	rip_v2_buf.rip.rip_cmd = RIPCMD_RESPONSE;
	rip_v2_buf.rip.rip_vers = RIPv2;
	v2buf.buf = &rip_v2_buf.rip;
	v2buf.base = &v2buf.buf->rip_nets[0];
}