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
struct sioc_mif_req6 {size_t mifi; int /*<<< orphan*/  obytes; int /*<<< orphan*/  ibytes; int /*<<< orphan*/  ocount; int /*<<< orphan*/  icount; } ;
typedef  size_t mifi_t ;
struct TYPE_2__ {int /*<<< orphan*/  m6_bytes_out; int /*<<< orphan*/  m6_bytes_in; int /*<<< orphan*/  m6_pkt_out; int /*<<< orphan*/  m6_pkt_in; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MIF6_LOCK () ; 
 int /*<<< orphan*/  MIF6_UNLOCK () ; 
 TYPE_1__* mif6table ; 
 size_t nummifs ; 

__attribute__((used)) static int
get_mif6_cnt(struct sioc_mif_req6 *req)
{
	mifi_t mifi;
	int ret;

	ret = 0;
	mifi = req->mifi;

	MIF6_LOCK();

	if (mifi >= nummifs) {
		ret = EINVAL;
	} else {
		req->icount = mif6table[mifi].m6_pkt_in;
		req->ocount = mif6table[mifi].m6_pkt_out;
		req->ibytes = mif6table[mifi].m6_bytes_in;
		req->obytes = mif6table[mifi].m6_bytes_out;
	}

	MIF6_UNLOCK();

	return (ret);
}