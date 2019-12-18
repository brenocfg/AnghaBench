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
struct tcp_req_info {struct sldns_buffer* spool_buffer; } ;
struct sldns_buffer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct tcp_req_info*,int /*<<< orphan*/ ,int) ; 

struct tcp_req_info*
tcp_req_info_create(struct sldns_buffer* spoolbuf)
{
	struct tcp_req_info* req = (struct tcp_req_info*)malloc(sizeof(*req));
	if(!req) {
		log_err("malloc failure for new stream outoforder processing structure");
		return NULL;
	}
	memset(req, 0, sizeof(*req));
	req->spool_buffer = spoolbuf;
	return req;
}