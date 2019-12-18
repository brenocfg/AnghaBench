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
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  em_dump_rs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_if_debug(if_ctx_t ctx)
{
	em_dump_rs(iflib_get_softc(ctx));
}