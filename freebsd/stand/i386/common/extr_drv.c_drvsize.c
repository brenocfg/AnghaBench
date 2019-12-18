#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct edd_params {int dummy; } ;
struct dsk {int /*<<< orphan*/  drive; } ;
struct TYPE_6__ {int len; int /*<<< orphan*/  sectors; } ;
struct TYPE_5__ {int addr; int eax; int /*<<< orphan*/  efl; int /*<<< orphan*/  esi; int /*<<< orphan*/  ds; int /*<<< orphan*/  edx; int /*<<< orphan*/  ctl; } ;

/* Variables and functions */
 scalar_t__ V86_CY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V86_FLAGS ; 
 int /*<<< orphan*/  VTOPOFF (TYPE_2__*) ; 
 int /*<<< orphan*/  VTOPSEG (TYPE_2__*) ; 
 TYPE_2__ params ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 TYPE_1__ v86 ; 
 int /*<<< orphan*/  v86int () ; 

uint64_t
drvsize(struct dsk *dskp)
{

	params.len = sizeof(struct edd_params);
	v86.ctl = V86_FLAGS;
	v86.addr = 0x13;
	v86.eax = 0x4800;
	v86.edx = dskp->drive;
	v86.ds = VTOPSEG(&params);
	v86.esi = VTOPOFF(&params);
	v86int();
	if (V86_CY(v86.efl)) {
		printf("error %u\n", v86.eax >> 8 & 0xff);
		return (0);
	}
	return (params.sectors);
}