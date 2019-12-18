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
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 scalar_t__ UCOM_UNIT_MAX ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_unrhdr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ucom_mtx ; 
 int /*<<< orphan*/  ucom_unrhdr ; 

__attribute__((used)) static void
ucom_init(void *arg)
{
	DPRINTF("\n");
	ucom_unrhdr = new_unrhdr(0, UCOM_UNIT_MAX - 1, NULL);
	mtx_init(&ucom_mtx, "UCOM MTX", NULL, MTX_DEF);
}