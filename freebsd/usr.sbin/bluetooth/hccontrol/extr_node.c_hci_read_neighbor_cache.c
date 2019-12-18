#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ng_btsocket_hci_raw_node_neighbor_cache {int num_entries; TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  r ;
typedef  int /*<<< orphan*/  ng_hci_node_neighbor_cache_entry_ep ;
typedef  int /*<<< orphan*/  addrtype2str ;
struct TYPE_3__ {int addrtype; int* features; int clock_offset; int page_scan_mode; int page_scan_rep_mode; int /*<<< orphan*/  extinq_size; int /*<<< orphan*/  extinq_data; int /*<<< orphan*/  bdaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int ERROR ; 
 int NG_HCI_MAX_NEIGHBOR_NUM ; 
 int OK ; 
 int /*<<< orphan*/  SIOC_HCI_RAW_NODE_GET_NEIGHBOR_CACHE ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 char* hci_bdaddr2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dump_adv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct ng_btsocket_hci_raw_node_neighbor_cache*,int) ; 
 int /*<<< orphan*/  memset (struct ng_btsocket_hci_raw_node_neighbor_cache*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int
hci_read_neighbor_cache(int s, int argc, char **argv)
{
	struct ng_btsocket_hci_raw_node_neighbor_cache	r;
	int						n, error = OK;
	const char  *addrtype2str[] = {"B", "P", "R", "E"};

	memset(&r, 0, sizeof(r));
	r.num_entries = NG_HCI_MAX_NEIGHBOR_NUM;
	r.entries = calloc(NG_HCI_MAX_NEIGHBOR_NUM,
				sizeof(ng_hci_node_neighbor_cache_entry_ep));
	if (r.entries == NULL) {
		errno = ENOMEM;
		return (ERROR);
	}

	if (ioctl(s, SIOC_HCI_RAW_NODE_GET_NEIGHBOR_CACHE, &r,
			sizeof(r)) < 0) {
		error = ERROR;
		goto out;
	}

	fprintf(stdout,
"T " \
"BD_ADDR           " \
"Features                " \
"Clock offset " \
"Page scan " \
"Rep. scan\n");

	for (n = 0; n < r.num_entries; n++) {
	        uint8_t addrtype = r.entries[n].addrtype;
		if(addrtype >= sizeof(addrtype2str)/sizeof(addrtype2str[0]))
			addrtype = sizeof(addrtype2str)/sizeof(addrtype2str[0]) - 1;
		fprintf(stdout, 
"%1s %-17.17s " \
"%02x %02x %02x %02x %02x %02x %02x %02x " \
"%#12x " \
"%#9x " \
"%#9x\n",
			addrtype2str[addrtype],
			hci_bdaddr2str(&r.entries[n].bdaddr),
			r.entries[n].features[0], r.entries[n].features[1],
			r.entries[n].features[2], r.entries[n].features[3],
			r.entries[n].features[4], r.entries[n].features[5],
			r.entries[n].features[6], r.entries[n].features[7],
			r.entries[n].clock_offset, r.entries[n].page_scan_mode,
			r.entries[n].page_scan_rep_mode);
		hci_dump_adv(r.entries[n].extinq_data,
			     r.entries[n].extinq_size);
		fprintf(stdout,"\n");
	}
out:
	free(r.entries);

	return (error);
}