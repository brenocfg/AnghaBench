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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  idr; } ;
struct kcs_bmc {TYPE_1__ ioreg; int /*<<< orphan*/  (* io_inputb ) (struct kcs_bmc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct kcs_bmc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 read_data(struct kcs_bmc *kcs_bmc)
{
	return kcs_bmc->io_inputb(kcs_bmc, kcs_bmc->ioreg.idr);
}