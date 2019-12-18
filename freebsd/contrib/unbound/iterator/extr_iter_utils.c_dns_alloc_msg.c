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
struct regional {int dummy; } ;
struct msg_parse {int dummy; } ;
struct dns_msg {int /*<<< orphan*/  rep; int /*<<< orphan*/  qinfo; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  memset (struct dns_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parse_create_msg (int /*<<< orphan*/ *,struct msg_parse*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct regional*) ; 
 scalar_t__ regional_alloc (struct regional*,int) ; 

struct dns_msg* 
dns_alloc_msg(sldns_buffer* pkt, struct msg_parse* msg, 
	struct regional* region)
{
	struct dns_msg* m = (struct dns_msg*)regional_alloc(region,
		sizeof(struct dns_msg));
	if(!m)
		return NULL;
	memset(m, 0, sizeof(*m));
	if(!parse_create_msg(pkt, msg, NULL, &m->qinfo, &m->rep, region)) {
		log_err("malloc failure: allocating incoming dns_msg");
		return NULL;
	}
	return m;
}