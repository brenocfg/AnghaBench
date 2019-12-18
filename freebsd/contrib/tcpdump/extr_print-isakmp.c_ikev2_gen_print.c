#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u_char ;
struct isakmp_gen {int /*<<< orphan*/  len; int /*<<< orphan*/  critical; } ;
struct TYPE_6__ {int ndo_vflag; } ;
typedef  TYPE_1__ netdissect_options ;
typedef  int /*<<< orphan*/  e ;

/* Variables and functions */
 int /*<<< orphan*/  ND_PRINT (TYPE_1__*) ; 
 int /*<<< orphan*/  ND_TCHECK (struct isakmp_gen const) ; 
 int /*<<< orphan*/  NPSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNALIGNED_MEMCPY (struct isakmp_gen*,struct isakmp_gen const*,int) ; 
 int /*<<< orphan*/  ikev2_pay_print (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rawprint (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const u_char *
ikev2_gen_print(netdissect_options *ndo, u_char tpay,
		const struct isakmp_gen *ext)
{
	struct isakmp_gen e;

	ND_TCHECK(*ext);
	UNALIGNED_MEMCPY(&e, ext, sizeof(e));
	ikev2_pay_print(ndo, NPSTR(tpay), e.critical);

	ND_PRINT((ndo," len=%d", ntohs(e.len) - 4));
	if (2 < ndo->ndo_vflag && 4 < ntohs(e.len)) {
		/* Print the entire payload in hex */
		ND_PRINT((ndo," "));
		if (!rawprint(ndo, (const uint8_t *)(ext + 1), ntohs(e.len) - 4))
			goto trunc;
	}
	return (const u_char *)ext + ntohs(e.len);
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(tpay)));
	return NULL;
}