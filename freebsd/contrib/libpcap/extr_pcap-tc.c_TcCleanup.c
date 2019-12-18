#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pcap_tc {int /*<<< orphan*/ * PpiPacket; int /*<<< orphan*/ * TcInstance; int /*<<< orphan*/ * TcPacketsBuffer; } ;
struct TYPE_5__ {struct pcap_tc* priv; } ;
typedef  TYPE_1__ pcap_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* InstanceClose ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* PacketsBufferDestroy ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 TYPE_3__ g_TcFunctions ; 
 int /*<<< orphan*/  pcap_cleanup_live_common (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void TcCleanup(pcap_t *p)
{
	struct pcap_tc *pt = p->priv;

	if (pt->TcPacketsBuffer != NULL)
	{
		g_TcFunctions.PacketsBufferDestroy(pt->TcPacketsBuffer);
		pt->TcPacketsBuffer = NULL;
	}
	if (pt->TcInstance != NULL)
	{
		/*
		 * here we do not check for the error values
		 */
		g_TcFunctions.InstanceClose(pt->TcInstance);
		pt->TcInstance = NULL;
	}

	if (pt->PpiPacket != NULL)
	{
		free(pt->PpiPacket);
		pt->PpiPacket = NULL;
	}

	pcap_cleanup_live_common(p);
}