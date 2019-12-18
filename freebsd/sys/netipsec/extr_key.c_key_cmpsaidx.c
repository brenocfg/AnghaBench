#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sa_len; } ;
struct TYPE_6__ {TYPE_1__ sa; } ;
struct secasindex {scalar_t__ proto; scalar_t__ mode; scalar_t__ reqid; TYPE_3__ dst; TYPE_3__ src; } ;

/* Variables and functions */
 int CMP_EXACTLY ; 
 int CMP_MODE_REQID ; 
 int CMP_REQID ; 
 scalar_t__ IPSEC_MODE_ANY ; 
 scalar_t__ bcmp (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ key_sockaddrcmp (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
key_cmpsaidx(const struct secasindex *saidx0, const struct secasindex *saidx1,
    int flag)
{

	/* sanity */
	if (saidx0 == NULL && saidx1 == NULL)
		return 1;

	if (saidx0 == NULL || saidx1 == NULL)
		return 0;

	if (saidx0->proto != saidx1->proto)
		return 0;

	if (flag == CMP_EXACTLY) {
		if (saidx0->mode != saidx1->mode)
			return 0;
		if (saidx0->reqid != saidx1->reqid)
			return 0;
		if (bcmp(&saidx0->src, &saidx1->src,
		    saidx0->src.sa.sa_len) != 0 ||
		    bcmp(&saidx0->dst, &saidx1->dst,
		    saidx0->dst.sa.sa_len) != 0)
			return 0;
	} else {

		/* CMP_MODE_REQID, CMP_REQID, CMP_HEAD */
		if (flag == CMP_MODE_REQID || flag == CMP_REQID) {
			/*
			 * If reqid of SPD is non-zero, unique SA is required.
			 * The result must be of same reqid in this case.
			 */
			if (saidx1->reqid != 0 &&
			    saidx0->reqid != saidx1->reqid)
				return 0;
		}

		if (flag == CMP_MODE_REQID) {
			if (saidx0->mode != IPSEC_MODE_ANY
			 && saidx0->mode != saidx1->mode)
				return 0;
		}

		if (key_sockaddrcmp(&saidx0->src.sa, &saidx1->src.sa, 0) != 0)
			return 0;
		if (key_sockaddrcmp(&saidx0->dst.sa, &saidx1->dst.sa, 0) != 0)
			return 0;
	}

	return 1;
}