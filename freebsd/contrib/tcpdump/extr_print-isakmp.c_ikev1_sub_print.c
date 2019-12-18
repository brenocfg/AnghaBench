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
typedef  int /*<<< orphan*/  u_char ;
struct isakmp_gen {int /*<<< orphan*/  np; int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  netdissect_options ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (struct isakmp_gen const) ; 
 int /*<<< orphan*/  ND_TCHECK2 (struct isakmp_gen const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NPSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (struct isakmp_gen*,struct isakmp_gen const*,int) ; 
 int /*<<< orphan*/ * ike_sub0_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct isakmp_gen const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static const u_char *
ikev1_sub_print(netdissect_options *ndo,
		u_char np, const struct isakmp_gen *ext, const u_char *ep,
		uint32_t phase, uint32_t doi, uint32_t proto, int depth)
{
	const u_char *cp;
	int i;
	struct isakmp_gen e;

	cp = (const u_char *)ext;

	while (np) {
		ND_TCHECK(*ext);
		UNALIGNED_MEMCPY(&e, ext, sizeof(e));

		ND_TCHECK2(*ext, ntohs(e.len));

		depth++;
		ND_PRINT((ndo,"\n"));
		for (i = 0; i < depth; i++)
			ND_PRINT((ndo,"    "));
		ND_PRINT((ndo,"("));
		cp = ike_sub0_print(ndo, np, ext, ep, phase, doi, proto, depth);
		ND_PRINT((ndo,")"));
		depth--;

		if (cp == NULL) {
			/* Zero-length subitem */
			return NULL;
		}

		np = e.np;
		ext = (const struct isakmp_gen *)cp;
	}
	return cp;
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(np)));
	return NULL;
}