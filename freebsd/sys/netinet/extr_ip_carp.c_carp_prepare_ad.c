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
struct mbuf {int dummy; } ;
struct m_tag {int dummy; } ;
struct carp_softc {int sc_counter; scalar_t__ sc_init_counter; } ;
struct carp_header {int /*<<< orphan*/  carp_md; void** carp_counter; } ;
typedef  int /*<<< orphan*/  sc ;

/* Variables and functions */
 int /*<<< orphan*/  CARPSTATS_INC (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  PACKET_TAG_CARP ; 
 int arc4random () ; 
 int /*<<< orphan*/  bcopy (struct carp_softc**,struct m_tag*,int) ; 
 int /*<<< orphan*/  carp_hmac_generate (struct carp_softc*,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  carps_onomem ; 
 void* htonl (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 struct m_tag* m_tag_get (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_tag_prepend (struct mbuf*,struct m_tag*) ; 

__attribute__((used)) static int
carp_prepare_ad(struct mbuf *m, struct carp_softc *sc, struct carp_header *ch)
{
	struct m_tag *mtag;

	if (sc->sc_init_counter) {
		/* this could also be seconds since unix epoch */
		sc->sc_counter = arc4random();
		sc->sc_counter = sc->sc_counter << 32;
		sc->sc_counter += arc4random();
	} else
		sc->sc_counter++;

	ch->carp_counter[0] = htonl((sc->sc_counter>>32)&0xffffffff);
	ch->carp_counter[1] = htonl(sc->sc_counter&0xffffffff);

	carp_hmac_generate(sc, ch->carp_counter, ch->carp_md);

	/* Tag packet for carp_output */
	if ((mtag = m_tag_get(PACKET_TAG_CARP, sizeof(struct carp_softc *),
	    M_NOWAIT)) == NULL) {
		m_freem(m);
		CARPSTATS_INC(carps_onomem);
		return (ENOMEM);
	}
	bcopy(&sc, mtag + 1, sizeof(sc));
	m_tag_prepend(m, mtag);

	return (0);
}