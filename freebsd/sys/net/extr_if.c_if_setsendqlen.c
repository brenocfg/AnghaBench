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
struct TYPE_2__ {int ifq_drv_maxlen; } ;
struct ifnet {TYPE_1__ if_snd; } ;
typedef  scalar_t__ if_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_1__*,int) ; 

int
if_setsendqlen(if_t ifp, int tx_desc_count)
{
	IFQ_SET_MAXLEN(&((struct ifnet *)ifp)->if_snd, tx_desc_count);
	((struct ifnet *)ifp)->if_snd.ifq_drv_maxlen = tx_desc_count;

	return (0);
}