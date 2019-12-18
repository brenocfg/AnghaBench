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
struct bcom_task {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  rx_ipr; int /*<<< orphan*/  rx_initiator; } ;

/* Variables and functions */
 unsigned int MPC52xx_PSC_MAXNUM ; 
 struct bcom_task* bcom_gen_bd_rx_init (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* bcom_psc_params ; 

struct bcom_task * bcom_psc_gen_bd_rx_init(unsigned psc_num, int queue_len,
					   phys_addr_t fifo, int maxbufsize)
{
	if (psc_num >= MPC52xx_PSC_MAXNUM)
		return NULL;

	return bcom_gen_bd_rx_init(queue_len, fifo,
				   bcom_psc_params[psc_num].rx_initiator,
				   bcom_psc_params[psc_num].rx_ipr,
				   maxbufsize);
}