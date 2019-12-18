#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct ibmad_port {int dummy; } ;
typedef  int /*<<< orphan*/  ib_portid_t ;

/* Variables and functions */
 int /*<<< orphan*/ * smp_query_status_via (void*,int /*<<< orphan*/ *,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ *,struct ibmad_port const*) ; 

uint8_t *smp_query_via(void *rcvbuf, ib_portid_t * portid, unsigned attrid,
		       unsigned mod, unsigned timeout,
		       const struct ibmad_port * srcport)
{
	return smp_query_status_via(rcvbuf, portid, attrid, mod, timeout, NULL,
				    srcport);
}