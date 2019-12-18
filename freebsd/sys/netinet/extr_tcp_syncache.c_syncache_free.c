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
struct syncache {int /*<<< orphan*/  sc_label; scalar_t__ sc_cred; scalar_t__ sc_ipopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  zone; } ;

/* Variables and functions */
 TYPE_1__ V_tcp_syncache ; 
 int /*<<< orphan*/  crfree (scalar_t__) ; 
 int /*<<< orphan*/  m_free (scalar_t__) ; 
 int /*<<< orphan*/  mac_syncache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct syncache*) ; 

__attribute__((used)) static void
syncache_free(struct syncache *sc)
{

	if (sc->sc_ipopts)
		(void) m_free(sc->sc_ipopts);
	if (sc->sc_cred)
		crfree(sc->sc_cred);
#ifdef MAC
	mac_syncache_destroy(&sc->sc_label);
#endif

	uma_zfree(V_tcp_syncache.zone, sc);
}