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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  size_t uint32_t ;
typedef  int u_char ;
struct attrmap {size_t nvalue; scalar_t__* value; scalar_t__ type; } ;
typedef  int /*<<< orphan*/  netdissect_options ;

/* Variables and functions */
 int EXTRACT_16BITS (int const*) ; 
 int /*<<< orphan*/  ND_PRINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ND_TCHECK (int const) ; 
 int /*<<< orphan*/  ND_TCHECK_16BITS (int const*) ; 
 int /*<<< orphan*/  rawprint (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const u_char *
ikev1_attrmap_print(netdissect_options *ndo,
		    const u_char *p, const u_char *ep2,
		    const struct attrmap *map, size_t nmap)
{
	int totlen;
	uint32_t t, v;

	ND_TCHECK(p[0]);
	if (p[0] & 0x80)
		totlen = 4;
	else {
		ND_TCHECK_16BITS(&p[2]);
		totlen = 4 + EXTRACT_16BITS(&p[2]);
	}
	if (ep2 < p + totlen) {
		ND_PRINT((ndo,"[|attr]"));
		return ep2 + 1;
	}

	ND_TCHECK_16BITS(&p[0]);
	ND_PRINT((ndo,"("));
	t = EXTRACT_16BITS(&p[0]) & 0x7fff;
	if (map && t < nmap && map[t].type)
		ND_PRINT((ndo,"type=%s ", map[t].type));
	else
		ND_PRINT((ndo,"type=#%d ", t));
	if (p[0] & 0x80) {
		ND_PRINT((ndo,"value="));
		ND_TCHECK_16BITS(&p[2]);
		v = EXTRACT_16BITS(&p[2]);
		if (map && t < nmap && v < map[t].nvalue && map[t].value[v])
			ND_PRINT((ndo,"%s", map[t].value[v]));
		else {
			if (!rawprint(ndo, (const uint8_t *)&p[2], 2)) {
				ND_PRINT((ndo,")"));
				goto trunc;
			}
		}
	} else {
		ND_PRINT((ndo,"len=%d value=", totlen - 4));
		if (!rawprint(ndo, (const uint8_t *)&p[4], totlen - 4)) {
			ND_PRINT((ndo,")"));
			goto trunc;
		}
	}
	ND_PRINT((ndo,")"));
	return p + totlen;

trunc:
	return NULL;
}