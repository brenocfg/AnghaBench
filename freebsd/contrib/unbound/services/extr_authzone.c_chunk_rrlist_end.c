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
struct auth_chunk {scalar_t__ len; struct auth_chunk* next; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_HEADER_SIZE ; 

__attribute__((used)) static int
chunk_rrlist_end(struct auth_chunk* rr_chunk, int rr_num)
{
	while(rr_chunk) {
		if(rr_chunk->len < LDNS_HEADER_SIZE)
			return 1;
		if(rr_num < (int)LDNS_ANCOUNT(rr_chunk->data))
			return 0;
		/* no more RRs in this chunk */
		/* continue with next chunk, see if it has RRs */
		rr_chunk = rr_chunk->next;
		rr_num = 0;
	}
	return 1;
}