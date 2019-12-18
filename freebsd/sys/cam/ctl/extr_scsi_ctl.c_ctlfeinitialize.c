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

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  STAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctlfe_driver ; 
 int /*<<< orphan*/  ctlfe_list_mtx ; 
 int /*<<< orphan*/  ctlfe_mtx_desc ; 
 int /*<<< orphan*/  ctlfe_softc_list ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  periphdriver_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ctlfeinitialize(void)
{

	STAILQ_INIT(&ctlfe_softc_list);
	mtx_init(&ctlfe_list_mtx, ctlfe_mtx_desc, NULL, MTX_DEF);
	periphdriver_register(&ctlfe_driver);
	return (0);
}