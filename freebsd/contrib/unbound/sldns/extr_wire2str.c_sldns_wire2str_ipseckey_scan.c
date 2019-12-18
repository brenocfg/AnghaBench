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

/* Variables and functions */
 int sldns_wire2str_ipseckey_scan_internal (int /*<<< orphan*/ **,size_t*,char**,size_t*,int /*<<< orphan*/ *,size_t) ; 

int sldns_wire2str_ipseckey_scan(uint8_t** d, size_t* dl, char** s, size_t* sl,
	uint8_t* pkt, size_t pktlen)
{
	uint8_t* od = *d;
	char* os = *s;
	size_t odl = *dl, osl = *sl;
	int w=sldns_wire2str_ipseckey_scan_internal(d, dl, s, sl, pkt, pktlen);
	if(w == -1) {
		*d = od;
		*s = os;
		*dl = odl;
		*sl = osl;
		return -1;
	}
	return w;
}