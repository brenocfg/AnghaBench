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
struct ifbreq {int ifbr_ifsflags; int ifbr_addrmax; int ifbr_portno; int ifbr_priority; int ifbr_path_cost; size_t ifbr_proto; size_t ifbr_role; size_t ifbr_state; int /*<<< orphan*/  ifbr_ifsname; } ;
struct ifbifconf {int ifbic_len; char* ifbic_buf; struct ifbreq* ifbic_req; } ;
typedef  int /*<<< orphan*/  bifc ;

/* Variables and functions */
 int /*<<< orphan*/  BRDGGIFS ; 
 int /*<<< orphan*/  IFBIFBITS ; 
 int IFBIF_STP ; 
 scalar_t__ do_cmd (int,int /*<<< orphan*/ ,struct ifbifconf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ isprint (char) ; 
 size_t nitems (char**) ; 
 int /*<<< orphan*/  printb (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* realloc (char*,int) ; 
 char** stpproto ; 
 char** stproles ; 
 char** stpstates ; 
 char* strdup (char const*) ; 

__attribute__((used)) static void
bridge_interfaces(int s, const char *prefix)
{
	struct ifbifconf bifc;
	struct ifbreq *req;
	char *inbuf = NULL, *ninbuf;
	char *p, *pad;
	int i, len = 8192;

	pad = strdup(prefix);
	if (pad == NULL)
		err(1, "strdup");
	/* replace the prefix with whitespace */
	for (p = pad; *p != '\0'; p++) {
		if(isprint(*p))
			*p = ' ';
	}

	for (;;) {
		ninbuf = realloc(inbuf, len);
		if (ninbuf == NULL)
			err(1, "unable to allocate interface buffer");
		bifc.ifbic_len = len;
		bifc.ifbic_buf = inbuf = ninbuf;
		if (do_cmd(s, BRDGGIFS, &bifc, sizeof(bifc), 0) < 0)
			err(1, "unable to get interface list");
		if ((bifc.ifbic_len + sizeof(*req)) < len)
			break;
		len *= 2;
	}

	for (i = 0; i < bifc.ifbic_len / sizeof(*req); i++) {
		req = bifc.ifbic_req + i;
		printf("%s%s ", prefix, req->ifbr_ifsname);
		printb("flags", req->ifbr_ifsflags, IFBIFBITS);
		printf("\n");

		printf("%s", pad);
		printf("ifmaxaddr %u", req->ifbr_addrmax);
		printf(" port %u priority %u", req->ifbr_portno,
		    req->ifbr_priority);
		printf(" path cost %u", req->ifbr_path_cost);

		if (req->ifbr_ifsflags & IFBIF_STP) {
			if (req->ifbr_proto < nitems(stpproto))
				printf(" proto %s", stpproto[req->ifbr_proto]);
			else
				printf(" <unknown proto %d>",
				    req->ifbr_proto);

			printf("\n%s", pad);
			if (req->ifbr_role < nitems(stproles))
				printf("role %s", stproles[req->ifbr_role]);
			else
				printf("<unknown role %d>",
				    req->ifbr_role);
			if (req->ifbr_state < nitems(stpstates))
				printf(" state %s", stpstates[req->ifbr_state]);
			else
				printf(" <unknown state %d>",
				    req->ifbr_state);
		}
		printf("\n");
	}
	free(pad);
	free(inbuf);
}