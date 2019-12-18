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
struct sfxge_softc {int dummy; } ;
struct sfxge_evq {struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  efx_link_mode_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_EVQ_LOCK_ASSERT_OWNED (struct sfxge_evq*) ; 
 int /*<<< orphan*/  sfxge_mac_link_update (struct sfxge_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
sfxge_ev_link_change(void *arg, efx_link_mode_t	link_mode)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;

	evq = (struct sfxge_evq *)arg;
	SFXGE_EVQ_LOCK_ASSERT_OWNED(evq);

	sc = evq->sc;

	sfxge_mac_link_update(sc, link_mode);

	return (0);
}