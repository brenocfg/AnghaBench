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
typedef  int /*<<< orphan*/  pcap_t ;

/* Variables and functions */
 scalar_t__ Iflag ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exit_tcpdump (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  has_printer (int) ; 
 char* pcap_datalink_val_to_description (int) ; 
 char* pcap_datalink_val_to_name (int) ; 
 int /*<<< orphan*/  pcap_free_datalinks (int*) ; 
 int /*<<< orphan*/  pcap_geterr (int /*<<< orphan*/ *) ; 
 int pcap_list_datalinks (int /*<<< orphan*/ *,int**) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ supports_monitor_mode ; 

__attribute__((used)) static void
show_dlts_and_exit(pcap_t *pc, const char *device)
{
	int n_dlts, i;
	int *dlts = 0;
	const char *dlt_name;

	n_dlts = pcap_list_datalinks(pc, &dlts);
	if (n_dlts < 0)
		error("%s", pcap_geterr(pc));
	else if (n_dlts == 0 || !dlts)
		error("No data link types.");

	/*
	 * If the interface is known to support monitor mode, indicate
	 * whether these are the data link types available when not in
	 * monitor mode, if -I wasn't specified, or when in monitor mode,
	 * when -I was specified (the link-layer types available in
	 * monitor mode might be different from the ones available when
	 * not in monitor mode).
	 */
	if (supports_monitor_mode)
		(void) fprintf(stderr, "Data link types for %s %s (use option -y to set):\n",
		    device,
		    Iflag ? "when in monitor mode" : "when not in monitor mode");
	else
		(void) fprintf(stderr, "Data link types for %s (use option -y to set):\n",
		    device);

	for (i = 0; i < n_dlts; i++) {
		dlt_name = pcap_datalink_val_to_name(dlts[i]);
		if (dlt_name != NULL) {
			(void) fprintf(stderr, "  %s (%s)", dlt_name,
			    pcap_datalink_val_to_description(dlts[i]));

			/*
			 * OK, does tcpdump handle that type?
			 */
			if (!has_printer(dlts[i]))
				(void) fprintf(stderr, " (printing not supported)");
			fprintf(stderr, "\n");
		} else {
			(void) fprintf(stderr, "  DLT %d (printing not supported)\n",
			    dlts[i]);
		}
	}
#ifdef HAVE_PCAP_FREE_DATALINKS
	pcap_free_datalinks(dlts);
#endif
	exit_tcpdump(0);
}