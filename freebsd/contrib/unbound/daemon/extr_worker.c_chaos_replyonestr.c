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
struct worker {int dummy; } ;
struct edns_data {int dummy; } ;
struct comm_reply {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  chaos_replystr (int /*<<< orphan*/ *,char**,int,struct edns_data*,struct worker*,struct comm_reply*) ; 

__attribute__((used)) static void
chaos_replyonestr(sldns_buffer* pkt, const char* str, struct edns_data* edns,
	struct worker* worker, struct comm_reply* repinfo)
{
	chaos_replystr(pkt, (char**)&str, 1, edns, worker, repinfo);
}