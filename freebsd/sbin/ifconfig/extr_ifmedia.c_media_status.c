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
struct ifmediareq {int ifm_count; int* ifm_ulist; scalar_t__ ifm_current; scalar_t__ ifm_active; int ifm_status; int ifdr_reason; char* ifdr_msg; int ifdr_vendor; int /*<<< orphan*/  ifdr_name; int /*<<< orphan*/  ifm_name; } ;
struct ifdownreason {int ifm_count; int* ifm_ulist; scalar_t__ ifm_current; scalar_t__ ifm_active; int ifm_status; int ifdr_reason; char* ifdr_msg; int ifdr_vendor; int /*<<< orphan*/  ifdr_name; int /*<<< orphan*/  ifm_name; } ;
typedef  int /*<<< orphan*/  ifmr ;
typedef  int /*<<< orphan*/  ifdr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
#define  IFDR_REASON_MSG 132 
#define  IFDR_REASON_VENDOR 131 
 int IFM_ACTIVE ; 
#define  IFM_ATM 130 
 int IFM_AVALID ; 
#define  IFM_ETHER 129 
#define  IFM_IEEE80211 128 
 int /*<<< orphan*/  IFM_IEEE80211_STA ; 
 int /*<<< orphan*/  IFM_OPMODE (scalar_t__) ; 
 int IFM_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  SIOCGIFDOWNREASON ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SIOCGIFXMEDIA ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  free (int*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct ifmediareq*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  name ; 
 int /*<<< orphan*/  print_media_word (scalar_t__,int) ; 
 int /*<<< orphan*/  print_media_word_ifconfig (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ supmedia ; 
 int /*<<< orphan*/  warnx (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
media_status(int s)
{
	struct ifmediareq ifmr;
	struct ifdownreason ifdr;
	int *media_list, i;
	bool no_carrier, xmedia;

	(void) memset(&ifmr, 0, sizeof(ifmr));
	(void) strlcpy(ifmr.ifm_name, name, sizeof(ifmr.ifm_name));
	xmedia = true;

	/*
	 * Check if interface supports extended media types.
	 */
	if (ioctl(s, SIOCGIFXMEDIA, (caddr_t)&ifmr) < 0)
		xmedia = false;
	if (!xmedia && ioctl(s, SIOCGIFMEDIA, (caddr_t)&ifmr) < 0) {
		/*
		 * Interface doesn't support SIOC{G,S}IFMEDIA.
		 */
		return;
	}

	if (ifmr.ifm_count == 0) {
		warnx("%s: no media types?", name);
		return;
	}

	media_list = (int *)malloc(ifmr.ifm_count * sizeof(int));
	if (media_list == NULL)
		err(1, "malloc");
	ifmr.ifm_ulist = media_list;

	if (xmedia) {
		if (ioctl(s, SIOCGIFXMEDIA, (caddr_t)&ifmr) < 0)
			err(1, "SIOCGIFXMEDIA");
	} else {
		if (ioctl(s, SIOCGIFMEDIA, (caddr_t)&ifmr) < 0)
			err(1, "SIOCGIFMEDIA");
	}

	printf("\tmedia: ");
	print_media_word(ifmr.ifm_current, 1);
	if (ifmr.ifm_active != ifmr.ifm_current) {
		putchar(' ');
		putchar('(');
		print_media_word(ifmr.ifm_active, 0);
		putchar(')');
	}

	putchar('\n');

	if (ifmr.ifm_status & IFM_AVALID) {
		no_carrier = false;
		printf("\tstatus: ");
		switch (IFM_TYPE(ifmr.ifm_active)) {
		case IFM_ETHER:
		case IFM_ATM:
			if (ifmr.ifm_status & IFM_ACTIVE)
				printf("active");
			else
				no_carrier = true;
			break;

		case IFM_IEEE80211:
			if (ifmr.ifm_status & IFM_ACTIVE) {
				/* NB: only sta mode associates */
				if (IFM_OPMODE(ifmr.ifm_active) == IFM_IEEE80211_STA)
					printf("associated");
				else
					printf("running");
			} else
				no_carrier = true;
			break;
		}
		if (no_carrier) {
			printf("no carrier");
			memset(&ifdr, 0, sizeof(ifdr));
			strlcpy(ifdr.ifdr_name, name, sizeof(ifdr.ifdr_name));
			if (ioctl(s, SIOCGIFDOWNREASON, (caddr_t)&ifdr) == 0) {
				switch (ifdr.ifdr_reason) {
				case IFDR_REASON_MSG:
					printf(" (%s)", ifdr.ifdr_msg);
					break;
				case IFDR_REASON_VENDOR:
					printf(" (vendor code %d)",
					    ifdr.ifdr_vendor);
					break;
				default:
					break;
				}
			}
		}
		putchar('\n');
	}

	if (ifmr.ifm_count > 0 && supmedia) {
		printf("\tsupported media:\n");
		for (i = 0; i < ifmr.ifm_count; i++) {
			printf("\t\t");
			print_media_word_ifconfig(media_list[i]);
			putchar('\n');
		}
	}

	free(media_list);
}