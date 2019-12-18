#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rh ;
struct TYPE_9__ {int /*<<< orphan*/  new_set; } ;
typedef  TYPE_2__ ipfw_range_tlv ;
struct TYPE_8__ {int length; int /*<<< orphan*/  type; } ;
struct TYPE_11__ {int /*<<< orphan*/  new_set; TYPE_1__ head; } ;
struct TYPE_10__ {TYPE_5__ range; int /*<<< orphan*/  opheader; } ;
typedef  TYPE_3__ ipfw_range_header ;

/* Variables and functions */
 int /*<<< orphan*/  IPFW_TLV_RANGE ; 
 scalar_t__ do_get3 (int,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
do_range_cmd(int cmd, ipfw_range_tlv *rt)
{
	ipfw_range_header rh;
	size_t sz;

	memset(&rh, 0, sizeof(rh));
	memcpy(&rh.range, rt, sizeof(*rt));
	rh.range.head.length = sizeof(*rt);
	rh.range.head.type = IPFW_TLV_RANGE;
	sz = sizeof(rh);

	if (do_get3(cmd, &rh.opheader, &sz) != 0)
		return (-1);
	/* Save number of matched objects */
	rt->new_set = rh.range.new_set;
	return (0);
}