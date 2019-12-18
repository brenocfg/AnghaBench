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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct grehdr {int /*<<< orphan*/  gre_flags; int /*<<< orphan*/ * gre_opts; } ;
struct gre_softc {int gre_options; int gre_hlen; scalar_t__ gre_key; scalar_t__ gre_oseq; } ;

/* Variables and functions */
 int GRE_ENABLE_CSUM ; 
 int GRE_ENABLE_SEQ ; 
 int /*<<< orphan*/  GRE_FLAGS_CP ; 
 int /*<<< orphan*/  GRE_FLAGS_KP ; 
 int /*<<< orphan*/  GRE_FLAGS_SP ; 
 int /*<<< orphan*/  SA_XLOCKED ; 
 int /*<<< orphan*/  gre_ioctl_sx ; 
 scalar_t__ htonl (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
gre_update_hdr(struct gre_softc *sc, struct grehdr *gh)
{
	uint32_t *opts;
	uint16_t flags;

	sx_assert(&gre_ioctl_sx, SA_XLOCKED);

	flags = 0;
	opts = gh->gre_opts;
	if (sc->gre_options & GRE_ENABLE_CSUM) {
		flags |= GRE_FLAGS_CP;
		sc->gre_hlen += 2 * sizeof(uint16_t);
		*opts++ = 0;
	}
	if (sc->gre_key != 0) {
		flags |= GRE_FLAGS_KP;
		sc->gre_hlen += sizeof(uint32_t);
		*opts++ = htonl(sc->gre_key);
	}
	if (sc->gre_options & GRE_ENABLE_SEQ) {
		flags |= GRE_FLAGS_SP;
		sc->gre_hlen += sizeof(uint32_t);
		*opts++ = 0;
	} else
		sc->gre_oseq = 0;
	gh->gre_flags = htons(flags);
}