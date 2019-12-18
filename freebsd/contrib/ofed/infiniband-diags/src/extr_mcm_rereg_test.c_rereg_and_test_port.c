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
typedef  int uint64_t ;
struct guid_trid {int guid; int* gid; scalar_t__ trid; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int* ibmad_gid_t ;
typedef  int /*<<< orphan*/  ib_portid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int MAX_CLIENTS ; 
 struct guid_trid* calloc (int,int) ; 
 int /*<<< orphan*/  err (char*,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  free (struct guid_trid*) ; 
 int htonll (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  rereg_query_all (int,int,int /*<<< orphan*/ *,struct guid_trid*,int) ; 
 int /*<<< orphan*/  rereg_recv_all (int,int,int /*<<< orphan*/ *,struct guid_trid*,int) ; 
 int /*<<< orphan*/  rereg_send_all (int,int,int /*<<< orphan*/ *,struct guid_trid*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int strtoull (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rereg_and_test_port(char *guid_file, int port, int agent,
			       ib_portid_t * dport, int timeout)
{
	char line[256];
	FILE *f;
	ibmad_gid_t port_gid;
	uint64_t prefix = htonll(0xfe80000000000000ull);
	uint64_t guid = htonll(0x0002c90200223825ull);
	struct guid_trid *list;
	int i = 0;

	list = calloc(MAX_CLIENTS, sizeof(*list));
	if (!list) {
		err("cannot alloc mem for guid/trid list: %s\n",
		    strerror(errno));
		return -1;
	}

	f = fopen(guid_file, "r");
	if (!f) {
		err("cannot open %s: %s\n", guid_file, strerror(errno));
		return -1;
	}

	while (fgets(line, sizeof(line), f)) {
		guid = strtoull(line, NULL, 0);
		guid = htonll(guid);
		memcpy(&port_gid[0], &prefix, 8);
		memcpy(&port_gid[8], &guid, 8);

		list[i].guid = guid;
		memcpy(list[i].gid, port_gid, sizeof(list[i].gid));
		list[i].trid = 0;
		if (++i >= MAX_CLIENTS)
			break;
	}
	fclose(f);

	rereg_send_all(port, agent, dport, list, i);
	rereg_recv_all(port, agent, dport, list, i);

	rereg_query_all(port, agent, dport, list, i);

	free(list);
	return 0;
}