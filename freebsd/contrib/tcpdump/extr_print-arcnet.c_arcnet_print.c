#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  u_char ;
struct arc_header {int /*<<< orphan*/  arc_dhost; int /*<<< orphan*/  arc_shost; int /*<<< orphan*/  arc_type; } ;
struct TYPE_4__ {scalar_t__ ndo_qflag; } ;
typedef  TYPE_1__ netdissect_options ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  arctypemap ; 
 char* tok2str (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
arcnet_print(netdissect_options *ndo, const u_char *bp, u_int length, int phds,
             int flag, u_int seqid)
{
	const struct arc_header *ap;
	const char *arctypename;


	ap = (const struct arc_header *)bp;


	if (ndo->ndo_qflag) {
		ND_PRINT((ndo, "%02x %02x %d: ",
			     ap->arc_shost,
			     ap->arc_dhost,
			     length));
		return;
	}

	arctypename = tok2str(arctypemap, "%02x", ap->arc_type);

	if (!phds) {
		ND_PRINT((ndo, "%02x %02x %s %d: ",
			     ap->arc_shost, ap->arc_dhost, arctypename,
			     length));
			     return;
	}

	if (flag == 0) {
		ND_PRINT((ndo, "%02x %02x %s seqid %04x %d: ",
			ap->arc_shost, ap->arc_dhost, arctypename, seqid,
			length));
			return;
	}

	if (flag & 1)
		ND_PRINT((ndo, "%02x %02x %s seqid %04x "
			"(first of %d fragments) %d: ",
			ap->arc_shost, ap->arc_dhost, arctypename, seqid,
			(flag + 3) / 2, length));
	else
		ND_PRINT((ndo, "%02x %02x %s seqid %04x "
			"(fragment %d) %d: ",
			ap->arc_shost, ap->arc_dhost, arctypename, seqid,
			flag/2 + 1, length));
}