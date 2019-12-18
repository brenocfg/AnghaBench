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
struct cryptop {int dummy; } ;
struct cpl_fw6_pld {int dummy; } ;
struct ccr_softc {int dummy; } ;
struct ccr_session {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int
ccr_gcm_done(struct ccr_softc *sc, struct ccr_session *s,
    struct cryptop *crp, const struct cpl_fw6_pld *cpl, int error)
{

	/*
	 * The updated IV to permit chained requests is at
	 * cpl->data[2], but OCF doesn't permit chained requests.
	 *
	 * Note that the hardware should always verify the GMAC hash.
	 */
	return (error);
}