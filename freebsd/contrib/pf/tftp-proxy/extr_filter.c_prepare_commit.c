#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct TYPE_5__ {int size; int esize; int /*<<< orphan*/  rs_num; int /*<<< orphan*/  anchor; struct TYPE_5__* array; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCXBEGIN ; 
 int /*<<< orphan*/  EINVAL ; 
 char* FTP_PROXY_ANCHOR ; 
 int PF_ANCHOR_NAME_SIZE ; 
 int /*<<< orphan*/  PF_RULESET_FILTER ; 
 int /*<<< orphan*/  PF_RULESET_NAT ; 
 int /*<<< orphan*/  PF_RULESET_RDR ; 
#define  TRANS_FILTER 130 
#define  TRANS_NAT 129 
#define  TRANS_RDR 128 
 int TRANS_SIZE ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  errno ; 
 int getpid () ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 TYPE_1__ pft ; 
 TYPE_1__* pfte ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

int
prepare_commit(u_int32_t id)
{
	char an[PF_ANCHOR_NAME_SIZE];
	int i;

	memset(&pft, 0, sizeof pft);
	pft.size = TRANS_SIZE;
	pft.esize = sizeof pfte[0];
	pft.array = pfte;

	snprintf(an, PF_ANCHOR_NAME_SIZE, "%s/%d.%d", FTP_PROXY_ANCHOR,
	    getpid(), id);
	for (i = 0; i < TRANS_SIZE; i++) {
		memset(&pfte[i], 0, sizeof pfte[0]);
		strlcpy(pfte[i].anchor, an, PF_ANCHOR_NAME_SIZE);
		switch (i) {
		case TRANS_FILTER:
			pfte[i].rs_num = PF_RULESET_FILTER;
			break;
		case TRANS_NAT:
			pfte[i].rs_num = PF_RULESET_NAT;
			break;
		case TRANS_RDR:
			pfte[i].rs_num = PF_RULESET_RDR;
			break;
		default:
			errno = EINVAL;
			return (-1);
		}
	}

	if (ioctl(dev, DIOCXBEGIN, &pft) == -1)
		return (-1);

	return (0);
}