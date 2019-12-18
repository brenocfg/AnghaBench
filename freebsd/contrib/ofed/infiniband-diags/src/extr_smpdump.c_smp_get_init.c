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
typedef  scalar_t__ uint16_t ;
struct drsmp {int base_version; int class_version; int method; int /*<<< orphan*/  tid; int /*<<< orphan*/  attr_mod; scalar_t__ attr_id; int /*<<< orphan*/  mgmt_class; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_SMI_CLASS ; 
 int /*<<< orphan*/  drmad_tid ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htonll (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct drsmp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ umad_get_mad (void*) ; 
 int /*<<< orphan*/  umad_set_addr (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void smp_get_init(void *umad, int lid, int attr, int mod)
{
	struct drsmp *smp = (struct drsmp *)(umad_get_mad(umad));

	memset(smp, 0, sizeof(*smp));

	smp->base_version = 1;
	smp->mgmt_class = IB_SMI_CLASS;
	smp->class_version = 1;

	smp->method = 1;
	smp->attr_id = (uint16_t) htons((uint16_t) attr);
	smp->attr_mod = htonl(mod);
	smp->tid = htonll(drmad_tid++);

	umad_set_addr(umad, lid, 0, 0, 0);
}