#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  bestat; } ;
struct TYPE_7__ {scalar_t__ gstat; scalar_t__ cstat; int /*<<< orphan*/  gerr; int /*<<< orphan*/  cerr; } ;
struct TYPE_6__ {int errstat; } ;
struct TYPE_5__ {int extio; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_err_addr ; 
 scalar_t__ cpu_err_stat ; 
 int extio_stat ; 
 int /*<<< orphan*/  gio_err_addr ; 
 scalar_t__ gio_err_stat ; 
 int /*<<< orphan*/  hpc3_berr_stat ; 
 TYPE_4__* hpc3c0 ; 
 scalar_t__ ip22_is_fullhouse () ; 
 TYPE_3__* sgimc ; 
 TYPE_2__* sgint ; 
 TYPE_1__* sgioc ; 

__attribute__((used)) static void save_and_clear_buserr(void)
{
	/* save status registers */
	cpu_err_addr = sgimc->cerr;
	cpu_err_stat = sgimc->cstat;
	gio_err_addr = sgimc->gerr;
	gio_err_stat = sgimc->gstat;
	extio_stat = ip22_is_fullhouse() ? sgioc->extio : (sgint->errstat << 4);
	hpc3_berr_stat = hpc3c0->bestat;

	sgimc->cstat = sgimc->gstat = 0;
}