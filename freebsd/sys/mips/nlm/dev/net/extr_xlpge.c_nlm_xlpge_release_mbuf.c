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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  int uint64_t ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  intmax_t ;

/* Variables and functions */
 int XLP_NTXFRAGS ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  nl_tx_desc_zone ; 
 int nlm_cpuid () ; 
 int nlm_paddr_ld (int) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void
nlm_xlpge_release_mbuf(uint64_t paddr)
{
	uint64_t	mag, desc, mbuf;

	paddr += (XLP_NTXFRAGS - 3) * sizeof(uint64_t);
	mag = nlm_paddr_ld(paddr);
	desc = nlm_paddr_ld(paddr + sizeof(uint64_t));
	mbuf = nlm_paddr_ld(paddr + 2 * sizeof(uint64_t));

	if (mag != 0xf00bad) {
		/* somebody else packet Error - FIXME in intialization */
		printf("cpu %d: ERR Tx packet paddr %jx, mag %jx, desc %jx mbuf %jx\n",
		    nlm_cpuid(), (uintmax_t)paddr, (uintmax_t)mag,
		    (intmax_t)desc, (uintmax_t)mbuf);
		return;
	}
	m_freem((struct mbuf *)(uintptr_t)mbuf);
	uma_zfree(nl_tx_desc_zone, (void *)(uintptr_t)desc);
}