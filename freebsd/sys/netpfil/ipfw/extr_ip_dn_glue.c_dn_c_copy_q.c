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
struct dn_flow_queue8 {int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_bytes; int /*<<< orphan*/  tot_pkts; } ;
struct dn_flow_queue7 {int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  id; int /*<<< orphan*/  len_bytes; int /*<<< orphan*/  len; } ;
struct dn_flow {int /*<<< orphan*/  drops; int /*<<< orphan*/  tot_bytes; int /*<<< orphan*/  tot_pkts; int /*<<< orphan*/  fid; int /*<<< orphan*/  len_bytes; int /*<<< orphan*/  length; } ;
struct copy_args {int* start; } ;

/* Variables and functions */
 scalar_t__ is7 ; 

int
dn_c_copy_q (void *_ni, void *arg)
{
	struct copy_args *a = arg;
	struct dn_flow_queue7 *fq7 = (struct dn_flow_queue7 *)*a->start;
	struct dn_flow_queue8 *fq8 = (struct dn_flow_queue8 *)*a->start;
	struct dn_flow *ni = (struct dn_flow *)_ni;
	int size = 0;

	/* XXX hash slot not set */
	/* No difference between 7.2/8 */
	fq7->len = ni->length;
	fq7->len_bytes = ni->len_bytes;
	fq7->id = ni->fid;

	if (is7) {
		size = sizeof(struct dn_flow_queue7);
		fq7->tot_pkts = ni->tot_pkts;
		fq7->tot_bytes = ni->tot_bytes;
		fq7->drops = ni->drops;
	} else {
		size = sizeof(struct dn_flow_queue8);
		fq8->tot_pkts = ni->tot_pkts;
		fq8->tot_bytes = ni->tot_bytes;
		fq8->drops = ni->drops;
	}

	*a->start += size;
	return 0;
}