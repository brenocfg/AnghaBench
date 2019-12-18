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
typedef  int uint8_t ;
typedef  size_t uint32_t ;
struct ctl_lun {int** pending_ua; int /*<<< orphan*/  lun_lock; } ;
typedef  int ctl_ua_type ;

/* Variables and functions */
 size_t CTL_MAX_INIT_PER_PORT ; 
 int CTL_UA_NONE ; 
 int CTL_UA_POWERON ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int SSD_KEY_UNIT_ATTENTION ; 
 int /*<<< orphan*/  ctl_ua_to_ascq (struct ctl_lun*,int,int*,int*,int*,int**) ; 
 int ffs (int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

ctl_ua_type
ctl_build_qae(struct ctl_lun *lun, uint32_t initidx, uint8_t *resp)
{
	ctl_ua_type ua;
	ctl_ua_type ua_to_build, ua_to_clear;
	uint8_t *info;
	int asc, ascq;
	uint32_t p, i;

	mtx_assert(&lun->lun_lock, MA_OWNED);
	p = initidx / CTL_MAX_INIT_PER_PORT;
	i = initidx % CTL_MAX_INIT_PER_PORT;
	if (lun->pending_ua[p] == NULL)
		ua = CTL_UA_POWERON;
	else
		ua = lun->pending_ua[p][i];
	if (ua == CTL_UA_NONE)
		return (CTL_UA_NONE);

	ua_to_build = (1 << (ffs(ua) - 1));
	ua_to_clear = ua_to_build;
	info = NULL;
	ctl_ua_to_ascq(lun, ua_to_build, &asc, &ascq, &ua_to_clear, &info);

	resp[0] = SSD_KEY_UNIT_ATTENTION;
	if (ua_to_build == ua)
		resp[0] |= 0x10;
	else
		resp[0] |= 0x20;
	resp[1] = asc;
	resp[2] = ascq;
	return (ua_to_build);
}