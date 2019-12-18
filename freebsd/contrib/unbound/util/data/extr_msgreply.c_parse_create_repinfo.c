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
struct msg_parse {int /*<<< orphan*/  rrset_count; int /*<<< orphan*/  ar_rrsets; int /*<<< orphan*/  ns_rrsets; int /*<<< orphan*/  an_rrsets; int /*<<< orphan*/  qdcount; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 struct reply_info* construct_reply_info_base (struct regional*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sec_status_unchecked ; 

__attribute__((used)) static int
parse_create_repinfo(struct msg_parse* msg, struct reply_info** rep,
	struct regional* region)
{
	*rep = construct_reply_info_base(region, msg->flags, msg->qdcount, 0, 
		0, 0, msg->an_rrsets, msg->ns_rrsets, msg->ar_rrsets, 
		msg->rrset_count, sec_status_unchecked);
	if(!*rep)
		return 0;
	return 1;
}