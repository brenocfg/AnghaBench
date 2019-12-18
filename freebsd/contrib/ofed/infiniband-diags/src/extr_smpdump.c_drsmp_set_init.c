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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
struct drsmp {int method; int dr_slid; int dr_dlid; scalar_t__ hop_cnt; int /*<<< orphan*/  data; int /*<<< orphan*/  initial_path; int /*<<< orphan*/  tid; int /*<<< orphan*/  attr_mod; scalar_t__ attr_id; } ;
struct TYPE_3__ {void* path; int hop_cnt; } ;
typedef  TYPE_1__ DRPath ;

/* Variables and functions */
 int /*<<< orphan*/  drmad_tid ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  htonll (int /*<<< orphan*/ ) ; 
 scalar_t__ htons (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  memset (struct drsmp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ umad_get_mad (void*) ; 
 int /*<<< orphan*/  umad_set_addr (void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void drsmp_set_init(void *umad, DRPath * path, int attr, int mod, void *data)
{
	struct drsmp *smp = (struct drsmp *)(umad_get_mad(umad));

	memset(smp, 0, sizeof(*smp));

	smp->method = 2;	/* SET */
	smp->attr_id = (uint16_t) htons((uint16_t) attr);
	smp->attr_mod = htonl(mod);
	smp->tid = htonll(drmad_tid++);
	smp->dr_slid = 0xffff;
	smp->dr_dlid = 0xffff;

	umad_set_addr(umad, 0xffff, 0, 0, 0);

	if (path)
		memcpy(smp->initial_path, path->path, path->hop_cnt + 1);

	if (data)
		memcpy(smp->data, data, sizeof smp->data);

	smp->hop_cnt = (uint8_t) path->hop_cnt;
}