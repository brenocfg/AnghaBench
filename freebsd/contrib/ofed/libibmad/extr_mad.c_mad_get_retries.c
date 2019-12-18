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
struct ibmad_port {int retries; } ;

/* Variables and functions */
 int madrpc_retries ; 

int mad_get_retries(const struct ibmad_port *srcport)
{
	return (srcport->retries ? srcport->retries : madrpc_retries);
}