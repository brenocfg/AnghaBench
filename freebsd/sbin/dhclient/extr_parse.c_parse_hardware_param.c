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
struct hardware {size_t hlen; int /*<<< orphan*/ * haddr; int /*<<< orphan*/  htype; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  COLON ; 
#define  ETHERNET 130 
#define  FDDI 129 
 int /*<<< orphan*/  HTYPE_ETHER ; 
 int /*<<< orphan*/  HTYPE_FDDI ; 
 int /*<<< orphan*/  HTYPE_IEEE802 ; 
 int SEMI ; 
#define  TOKEN_RING 128 
 int /*<<< orphan*/  free (unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int next_token (char**,int /*<<< orphan*/ *) ; 
 unsigned char* parse_numeric_aggregate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  parse_warn (char*) ; 
 int /*<<< orphan*/  skip_to_semi (int /*<<< orphan*/ *) ; 

void
parse_hardware_param(FILE *cfile, struct hardware *hardware)
{
	unsigned char *t;
	int token;
	size_t hlen;
	char *val;

	token = next_token(&val, cfile);
	switch (token) {
	case ETHERNET:
		hardware->htype = HTYPE_ETHER;
		break;
	case TOKEN_RING:
		hardware->htype = HTYPE_IEEE802;
		break;
	case FDDI:
		hardware->htype = HTYPE_FDDI;
		break;
	default:
		parse_warn("expecting a network hardware type");
		skip_to_semi(cfile);
		return;
	}

	/*
	 * Parse the hardware address information.   Technically, it
	 * would make a lot of sense to restrict the length of the data
	 * we'll accept here to the length of a particular hardware
	 * address type.   Unfortunately, there are some broken clients
	 * out there that put bogus data in the chaddr buffer, and we
	 * accept that data in the lease file rather than simply failing
	 * on such clients.   Yuck.
	 */
	hlen = 0;
	t = parse_numeric_aggregate(cfile, NULL, &hlen, COLON, 16, 8);
	if (!t)
		return;
	if (hlen > sizeof(hardware->haddr)) {
		free(t);
		parse_warn("hardware address too long");
	} else {
		hardware->hlen = hlen;
		memcpy((unsigned char *)&hardware->haddr[0], t,
		    hardware->hlen);
		if (hlen < sizeof(hardware->haddr))
			memset(&hardware->haddr[hlen], 0,
			    sizeof(hardware->haddr) - hlen);
		free(t);
	}

	token = next_token(&val, cfile);
	if (token != SEMI) {
		parse_warn("expecting semicolon.");
		skip_to_semi(cfile);
	}
}