#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct firewire_header {int /*<<< orphan*/  firewire_type; int /*<<< orphan*/  firewire_dhost; int /*<<< orphan*/  firewire_shost; } ;
struct TYPE_5__ {int /*<<< orphan*/  ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  EXTRACT_16BITS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ethertype_values ; 
 int /*<<< orphan*/  fwaddr_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
ap1394_hdr_print(netdissect_options *ndo, register const u_char *bp, u_int length)
{
	register const struct firewire_header *fp;
	uint16_t firewire_type;

	fp = (const struct firewire_header *)bp;

	ND_PRINT((ndo, "%s > %s",
		     fwaddr_string(ndo, fp->firewire_shost),
		     fwaddr_string(ndo, fp->firewire_dhost)));

	firewire_type = EXTRACT_16BITS(&fp->firewire_type);
	if (!ndo->ndo_qflag) {
		ND_PRINT((ndo, ", ethertype %s (0x%04x)",
			       tok2str(ethertype_values,"Unknown", firewire_type),
                               firewire_type));
        } else {
                ND_PRINT((ndo, ", %s", tok2str(ethertype_values,"Unknown Ethertype (0x%04x)", firewire_type)));
        }

	ND_PRINT((ndo, ", length %u: ", length));
}