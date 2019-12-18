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
struct reply_info {int dummy; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
struct msg_parse {int dummy; } ;
struct alloc_cache {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  parse_copy_decompress (int /*<<< orphan*/ *,struct msg_parse*,struct reply_info*,struct regional*) ; 
 int /*<<< orphan*/  parse_create_qinfo (int /*<<< orphan*/ *,struct msg_parse*,struct query_info*,struct regional*) ; 
 int /*<<< orphan*/  parse_create_repinfo (struct msg_parse*,struct reply_info**,struct regional*) ; 
 int /*<<< orphan*/  reply_info_alloc_rrset_keys (struct reply_info*,struct alloc_cache*,struct regional*) ; 
 int /*<<< orphan*/  reply_info_parsedelete (struct reply_info*,struct alloc_cache*) ; 

int 
parse_create_msg(sldns_buffer* pkt, struct msg_parse* msg,
	struct alloc_cache* alloc, struct query_info* qinf, 
	struct reply_info** rep, struct regional* region)
{
	log_assert(pkt && msg);
	if(!parse_create_qinfo(pkt, msg, qinf, region))
		return 0;
	if(!parse_create_repinfo(msg, rep, region))
		return 0;
	if(!reply_info_alloc_rrset_keys(*rep, alloc, region)) {
		if(!region) reply_info_parsedelete(*rep, alloc);
		return 0;
	}
	if(!parse_copy_decompress(pkt, msg, *rep, region)) {
		if(!region) reply_info_parsedelete(*rep, alloc);
		return 0;
	}
	return 1;
}