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
struct TYPE_2__ {struct nfe_desc32* desc32; struct nfe_desc64* desc64; struct nfe_rx_data* data; } ;
struct nfe_softc {int nfe_flags; TYPE_1__ rxq; } ;
struct nfe_rx_data {int /*<<< orphan*/  paddr; struct mbuf* m; } ;
struct nfe_desc64 {void* flags; void* length; void** physaddr; } ;
struct nfe_desc32 {void* flags; void* length; } ;
struct mbuf {int /*<<< orphan*/  m_len; } ;

/* Variables and functions */
 int NFE_40BIT_ADDR ; 
 int /*<<< orphan*/  NFE_ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_ADDR_LO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_RX_READY ; 
 void* htole16 (int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
nfe_discard_rxbuf(struct nfe_softc *sc, int idx)
{
	struct nfe_desc32 *desc32;
	struct nfe_desc64 *desc64;
	struct nfe_rx_data *data;
	struct mbuf *m;

	data = &sc->rxq.data[idx];
	m = data->m;

	if (sc->nfe_flags & NFE_40BIT_ADDR) {
		desc64 = &sc->rxq.desc64[idx];
		/* VLAN packet may have overwritten it. */
		desc64->physaddr[0] = htole32(NFE_ADDR_HI(data->paddr));
		desc64->physaddr[1] = htole32(NFE_ADDR_LO(data->paddr));
		desc64->length = htole16(m->m_len);
		desc64->flags = htole16(NFE_RX_READY);
	} else {
		desc32 = &sc->rxq.desc32[idx];
		desc32->length = htole16(m->m_len);
		desc32->flags = htole16(NFE_RX_READY);
	}
}