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
struct bnxt_softc {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_get_wol_settings (struct bnxt_softc*) ; 
 struct bnxt_softc* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_resume(if_ctx_t ctx)
{
	struct bnxt_softc *softc = iflib_get_softc(ctx);

	bnxt_get_wol_settings(softc);
	return 0;
}