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
struct reply_info {int /*<<< orphan*/  flags; } ;
struct regional {int dummy; } ;
struct query_info {int dummy; } ;
typedef  int /*<<< orphan*/  sldns_buffer ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  log_info (char*,char const*,...) ; 
 struct regional* regional_create () ; 
 int /*<<< orphan*/  regional_destroy (struct regional*) ; 
 int /*<<< orphan*/  reply_info_encode (struct query_info*,struct reply_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct regional*,int,int) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sldns_buffer_new (int) ; 
 char* sldns_wire2str_pkt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void 
log_dns_msg(const char* str, struct query_info* qinfo, struct reply_info* rep)
{
	/* not particularly fast but flexible, make wireformat and print */
	sldns_buffer* buf = sldns_buffer_new(65535);
	struct regional* region = regional_create();
	if(!reply_info_encode(qinfo, rep, 0, rep->flags, buf, 0, 
		region, 65535, 1)) {
		log_info("%s: log_dns_msg: out of memory", str);
	} else {
		char* s = sldns_wire2str_pkt(sldns_buffer_begin(buf),
			sldns_buffer_limit(buf));
		if(!s) {
			log_info("%s: log_dns_msg: ldns tostr failed", str);
		} else {
			log_info("%s %s", str, s);
		}
		free(s);
	}
	sldns_buffer_free(buf);
	regional_destroy(region);
}