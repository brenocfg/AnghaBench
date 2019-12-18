#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct pfsync_subheader {size_t action; int /*<<< orphan*/  count; } ;
struct pfsync_header {scalar_t__ version; int /*<<< orphan*/  len; } ;
struct TYPE_6__ {scalar_t__ ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
struct TYPE_7__ {int len; int /*<<< orphan*/  (* print ) (TYPE_1__*,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 size_t PFSYNC_ACT_EOF ; 
 size_t PFSYNC_ACT_MAX ; 
 scalar_t__ PFSYNC_VERSION ; 
 TYPE_4__* actions ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void
pfsync_print(netdissect_options *ndo, struct pfsync_header *hdr,
    const u_char *bp, u_int len)
{
	struct pfsync_subheader *subh;
	int count, plen, i;
	u_int alen;

	plen = ntohs(hdr->len);

	ND_PRINT((ndo, "PFSYNCv%d len %d", hdr->version, plen));

	if (hdr->version != PFSYNC_VERSION)
		return;

	plen -= sizeof(*hdr);

	while (plen > 0) {
		if (len < sizeof(*subh))
			break;

		subh = (struct pfsync_subheader *)bp;
		bp += sizeof(*subh);
		len -= sizeof(*subh);
		plen -= sizeof(*subh);

		if (subh->action >= PFSYNC_ACT_MAX) {
			ND_PRINT((ndo, "\n    act UNKNOWN id %d",
			    subh->action));
			return;
		}

		count = ntohs(subh->count);
		ND_PRINT((ndo, "\n    %s count %d", actions[subh->action].name,
		    count));
		alen = actions[subh->action].len;

		if (subh->action == PFSYNC_ACT_EOF)
			return;

		if (actions[subh->action].print == NULL) {
			ND_PRINT((ndo, "\n    unimplemented action %hhu",
			    subh->action));
			return;
		}

		for (i = 0; i < count; i++) {
			if (len < alen) {
				len = 0;
				break;
			}

			if (ndo->ndo_vflag)
				actions[subh->action].print(ndo, bp);

			bp += alen;
			len -= alen;
			plen -= alen;
		}
	}

	if (plen > 0) {
		ND_PRINT((ndo, "\n    ..."));
		return;
	}
	if (plen < 0) {
		ND_PRINT((ndo, "\n    invalid header length"));
		return;
	}
	if (len > 0)
		ND_PRINT((ndo, "\n    invalid packet length"));
}