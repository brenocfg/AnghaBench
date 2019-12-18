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
struct ifmediareq {scalar_t__ ifm_current; scalar_t__ ifm_active; int ifm_status; int ifm_count; scalar_t__* ifm_ulist; } ;
struct ifaddrs {int /*<<< orphan*/  ifa_name; } ;
typedef  int /*<<< orphan*/  opts ;
typedef  int /*<<< orphan*/  ifconfig_handle_t ;

/* Variables and functions */
 int IFM_AVALID ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (struct ifmediareq*) ; 
 scalar_t__ ifconfig_err_errtype (int /*<<< orphan*/ *) ; 
 scalar_t__ ifconfig_media_get_mediareq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ifmediareq**) ; 
 int /*<<< orphan*/  ifconfig_media_get_options_string (scalar_t__,char*,int) ; 
 char* ifconfig_media_get_status (struct ifmediareq*) ; 
 char* ifconfig_media_get_subtype (scalar_t__) ; 
 char* ifconfig_media_get_type (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
print_media(ifconfig_handle_t *lifh, struct ifaddrs *ifa)
{
	int i;

	/* Outline:
	 * 1) Determine whether the iface supports SIOGIFMEDIA or SIOGIFXMEDIA
	 * 2) Get the full media list
	 * 3) Print the current media word
	 * 4) Print the active media word, if different
	 * 5) Print the status
	 * 6) Print the supported media list
	 *
	 * How to print the media word:
	 * 1) Get the top-level interface type and description
	 * 2) Print the subtype
	 * 3) For current word only, print the top type, if it exists
	 * 4) Print options list
	 * 5) Print the instance, if there is one
	 *
	 * How to get the top-level interface type
	 * 1) Shift ifmw right by 0x20 and index into IFM_TYPE_DESCRIPTIONS
	 *
	 * How to get the top-level interface subtype
	 * 1) Shift ifmw right by 0x20, index into ifmedia_types_to_subtypes
	 * 2) Iterate through the resulting table's subtypes table, ignoring
	 *    aliases.  Iterate through the resulting ifmedia_description
	 *    tables,  finding an entry with the right media subtype
	 */
	struct ifmediareq *ifmr;
	char opts[80];

	if (ifconfig_media_get_mediareq(lifh, ifa->ifa_name, &ifmr) != 0) {
		if (ifconfig_err_errtype(lifh) != OK) {
			err(1, "Failed to get media info");
		} else {
			return; /* Interface doesn't support media info */
		}
	}

	printf("\tmedia: %s %s", ifconfig_media_get_type(ifmr->ifm_current),
	    ifconfig_media_get_subtype(ifmr->ifm_current));
	if (ifmr->ifm_active != ifmr->ifm_current) {
		printf(" (%s", ifconfig_media_get_subtype(ifmr->ifm_active));
		ifconfig_media_get_options_string(ifmr->ifm_active, opts,
		    sizeof(opts));
		if (opts[0] != '\0') {
			printf(" <%s>)\n", opts);
		} else {
			printf(")\n");
		}
	} else {
		printf("\n");
	}

	if (ifmr->ifm_status & IFM_AVALID) {
		printf("\tstatus: %s\n",
		    ifconfig_media_get_status(ifmr));
	}

	printf("\tsupported media:\n");
	for (i = 0; i < ifmr->ifm_count; i++) {
		printf("\t\tmedia %s",
		    ifconfig_media_get_subtype(ifmr->ifm_ulist[i]));
		ifconfig_media_get_options_string(ifmr->ifm_ulist[i], opts,
		    sizeof(opts));
		if (opts[0] != '\0') {
			printf(" mediaopt %s\n", opts);
		} else {
			printf("\n");
		}
	}
	free(ifmr);
}