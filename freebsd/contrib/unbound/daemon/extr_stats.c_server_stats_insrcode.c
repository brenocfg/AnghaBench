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
struct ub_server_stats {int /*<<< orphan*/  ans_rcode_nodata; int /*<<< orphan*/ * ans_rcode; scalar_t__ extended; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 scalar_t__ LDNS_ANCOUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ LDNS_RCODE_WIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ *) ; 

void server_stats_insrcode(struct ub_server_stats* stats, sldns_buffer* buf)
{
	if(stats->extended && sldns_buffer_limit(buf) != 0) {
		int r = (int)LDNS_RCODE_WIRE( sldns_buffer_begin(buf) );
		stats->ans_rcode[r] ++;
		if(r == 0 && LDNS_ANCOUNT( sldns_buffer_begin(buf) ) == 0)
			stats->ans_rcode_nodata ++;
	}
}