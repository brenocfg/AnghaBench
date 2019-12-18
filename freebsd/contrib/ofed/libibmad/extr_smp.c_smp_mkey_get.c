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
typedef  int /*<<< orphan*/  uint64_t ;
struct ibmad_port {int /*<<< orphan*/  smp_mkey; } ;

/* Variables and functions */

uint64_t smp_mkey_get(const struct ibmad_port *srcport)
{
	return srcport->smp_mkey;
}