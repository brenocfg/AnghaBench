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
struct reply_info {scalar_t__ an_numrrsets; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flags; } ;
struct lruhash_entry {scalar_t__ data; } ;
struct del_info {int /*<<< orphan*/  num_msgs; int /*<<< orphan*/  expired; } ;

/* Variables and functions */
 scalar_t__ FLAGS_GET_RCODE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
negative_del_msg(struct lruhash_entry* e, void* arg)
{
	/* entry is locked */
	struct del_info* inf = (struct del_info*)arg;
	struct reply_info* d = (struct reply_info*)e->data;
	/* rcode not NOERROR: NXDOMAIN, SERVFAIL, ..: an nxdomain or error
	 * or NOERROR rcode with ANCOUNT==0: a NODATA answer */
	if(FLAGS_GET_RCODE(d->flags) != 0 || d->an_numrrsets == 0) {
		d->ttl = inf->expired;
		inf->num_msgs++;
	}
}