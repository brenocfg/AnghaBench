#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct mwl_hal_priv {int /*<<< orphan*/  mh_dev; scalar_t__ mh_cmdbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  Result; int /*<<< orphan*/  SeqNum; int /*<<< orphan*/  Cmd; int /*<<< orphan*/  MacId; int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ FWCmdHdr ;

/* Variables and functions */
 int HostCmd_RESULT_PARTIAL_DATA ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,...) ; 
 int le16toh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwlcmdname (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
dumpresult(struct mwl_hal_priv *mh, int showresult)
{
	const FWCmdHdr *h = (const FWCmdHdr *)mh->mh_cmdbuf;
	const uint8_t *cp;
	int len, i;

	len = le16toh(h->Length);
#ifdef MWL_MBSS_SUPPORT
	device_printf(mh->mh_dev, "Cmd %s Length %d SeqNum %d MacId %d",
	    mwlcmdname(le16toh(h->Cmd) &~ 0x8000), len, h->SeqNum, h->MacId);
#else
	device_printf(mh->mh_dev, "Cmd %s Length %d SeqNum %d",
	    mwlcmdname(le16toh(h->Cmd) &~ 0x8000), len, le16toh(h->SeqNum));
#endif
	if (showresult) {
		const char *results[] =
		    { "OK", "ERROR", "NOT_SUPPORT", "PENDING", "BUSY",
		      "PARTIAL_DATA" };
		int result = le16toh(h->Result);

		if (result <= HostCmd_RESULT_PARTIAL_DATA)
			printf(" Result %s", results[result]);
		else
			printf(" Result %d", result);
	}
	cp = (const uint8_t *)h;
	for (i = 0; i < len; i++) {
		if ((i % 16) == 0)
			printf("\n%02x", cp[i]);
		else
			printf(" %02x", cp[i]);
	}
	printf("\n");
}