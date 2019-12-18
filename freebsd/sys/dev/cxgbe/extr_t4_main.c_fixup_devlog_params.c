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
struct devlog_params {int /*<<< orphan*/  addr; int /*<<< orphan*/  size; int /*<<< orphan*/  start; int /*<<< orphan*/  memtype; } ;
struct TYPE_2__ {struct devlog_params devlog; } ;
struct adapter {TYPE_1__ params; } ;

/* Variables and functions */
 int validate_mt_off_len (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
fixup_devlog_params(struct adapter *sc)
{
	struct devlog_params *dparams = &sc->params.devlog;
	int rc;

	rc = validate_mt_off_len(sc, dparams->memtype, dparams->start,
	    dparams->size, &dparams->addr);

	return (rc);
}