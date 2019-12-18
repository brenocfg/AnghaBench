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
struct ldc_version {scalar_t__ major; scalar_t__ minor; } ;
struct ldc_channel {scalar_t__ hs_state; struct ldc_version ver; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS ; 
 int LDC_ABORT (struct ldc_channel*) ; 
 scalar_t__ LDC_HS_GOTVERS ; 
 scalar_t__ LDC_HS_OPEN ; 
 struct ldc_version* find_by_major (scalar_t__) ; 
 int /*<<< orphan*/  ldcdbg (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct ldc_version*,int /*<<< orphan*/ ,int) ; 
 int send_version_ack (struct ldc_channel*,struct ldc_version*) ; 
 int send_version_nack (struct ldc_channel*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int process_ver_info(struct ldc_channel *lp, struct ldc_version *vp)
{
	struct ldc_version *vap;
	int err;

	ldcdbg(HS, "GOT VERSION INFO major[%x] minor[%x]\n",
	       vp->major, vp->minor);

	if (lp->hs_state == LDC_HS_GOTVERS) {
		lp->hs_state = LDC_HS_OPEN;
		memset(&lp->ver, 0, sizeof(lp->ver));
	}

	vap = find_by_major(vp->major);
	if (!vap) {
		err = send_version_nack(lp, 0, 0);
	} else if (vap->major != vp->major) {
		err = send_version_nack(lp, vap->major, vap->minor);
	} else {
		struct ldc_version ver = *vp;
		if (ver.minor > vap->minor)
			ver.minor = vap->minor;
		err = send_version_ack(lp, &ver);
		if (!err) {
			lp->ver = ver;
			lp->hs_state = LDC_HS_GOTVERS;
		}
	}
	if (err)
		return LDC_ABORT(lp);

	return 0;
}