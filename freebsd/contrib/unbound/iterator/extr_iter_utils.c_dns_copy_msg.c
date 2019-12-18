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
struct regional {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  qname_len; int /*<<< orphan*/  qname; } ;
struct dns_msg {int /*<<< orphan*/  rep; TYPE_1__ qinfo; } ;

/* Variables and functions */
 scalar_t__ regional_alloc (struct regional*,int) ; 
 int /*<<< orphan*/  regional_alloc_init (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reply_info_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regional*) ; 

struct dns_msg* 
dns_copy_msg(struct dns_msg* from, struct regional* region)
{
	struct dns_msg* m = (struct dns_msg*)regional_alloc(region,
		sizeof(struct dns_msg));
	if(!m)
		return NULL;
	m->qinfo = from->qinfo;
	if(!(m->qinfo.qname = regional_alloc_init(region, from->qinfo.qname,
		from->qinfo.qname_len)))
		return NULL;
	if(!(m->rep = reply_info_copy(from->rep, NULL, region)))
		return NULL;
	return m;
}