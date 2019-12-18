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
struct atm_dev {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int GET (int /*<<< orphan*/ ) ; 
 TYPE_1__* PRIV (struct atm_dev*) ; 
 int /*<<< orphan*/  PUT (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_CHANGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RPOP_RC ; 
 int /*<<< orphan*/  SPTB_CTRL ; 
 int /*<<< orphan*/  SSTB_CTRL ; 
 scalar_t__ SUNI_MRI_TYPE_PM5355 ; 
 int SUNI_RPOP_RC_ENSS ; 
 int SUNI_SPTB_CTRL_LEN16 ; 
 int SUNI_SSTB_CTRL_LEN16 ; 
 int /*<<< orphan*/  SUNI_TPOP_APM_S ; 
 int /*<<< orphan*/  SUNI_TPOP_APM_S_SHIFT ; 
 int /*<<< orphan*/  SUNI_TPOP_S_SONET ; 
 int /*<<< orphan*/  TPOP_APM ; 

__attribute__((used)) static int set_sonet(struct atm_dev *dev)
{
	if (PRIV(dev)->type == SUNI_MRI_TYPE_PM5355) {
		PUT(GET(RPOP_RC) & ~SUNI_RPOP_RC_ENSS, RPOP_RC);
		PUT(GET(SSTB_CTRL) & ~SUNI_SSTB_CTRL_LEN16, SSTB_CTRL);
		PUT(GET(SPTB_CTRL) & ~SUNI_SPTB_CTRL_LEN16, SPTB_CTRL);
	}

	REG_CHANGE(SUNI_TPOP_APM_S, SUNI_TPOP_APM_S_SHIFT,
		   SUNI_TPOP_S_SONET, TPOP_APM);

	return 0;
}