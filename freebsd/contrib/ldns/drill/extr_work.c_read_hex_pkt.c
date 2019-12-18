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
typedef  scalar_t__ ldns_status ;
typedef  int /*<<< orphan*/  ldns_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_ERR ; 
 scalar_t__ LDNS_STATUS_OK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* ldns_get_errorstr_by_id (scalar_t__) ; 
 scalar_t__ ldns_wire2pkt (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 size_t packetbuffromfile (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * xmalloc (int /*<<< orphan*/ ) ; 

ldns_pkt *
read_hex_pkt(char *filename)
{
	uint8_t *wire;
	size_t wiresize;
	
	ldns_pkt *pkt = NULL;
	
	ldns_status status = LDNS_STATUS_ERR;

	wire = xmalloc(LDNS_MAX_PACKETLEN);
	
	wiresize = packetbuffromfile(filename, wire);
	
	if (wiresize > 0) {
		status = ldns_wire2pkt(&pkt, wire, wiresize);
	}
	
	xfree(wire);
	
	if (status == LDNS_STATUS_OK) {
		return pkt;
	} else {
		fprintf(stderr, "Error parsing hex file: %s\n",
			   ldns_get_errorstr_by_id(status));
		return NULL;
	}
}