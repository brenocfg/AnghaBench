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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;
struct fetch_negotiator {struct object_id* (* next ) (struct fetch_negotiator*) ;} ;

/* Variables and functions */
 int MAX_IN_VAIN ; 
 int next_flush (int,int) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  packet_buf_write (struct strbuf*,char*,...) ; 
 struct object_id* stub1 (struct fetch_negotiator*) ; 

__attribute__((used)) static int add_haves(struct fetch_negotiator *negotiator,
		     struct strbuf *req_buf,
		     int *haves_to_send, int *in_vain)
{
	int ret = 0;
	int haves_added = 0;
	const struct object_id *oid;

	while ((oid = negotiator->next(negotiator))) {
		packet_buf_write(req_buf, "have %s\n", oid_to_hex(oid));
		if (++haves_added >= *haves_to_send)
			break;
	}

	*in_vain += haves_added;
	if (!haves_added || *in_vain >= MAX_IN_VAIN) {
		/* Send Done */
		packet_buf_write(req_buf, "done\n");
		ret = 1;
	}

	/* Increase haves to send on next round */
	*haves_to_send = next_flush(1, *haves_to_send);

	return ret;
}