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
typedef  int uint32_t ;
struct isns_req {int ir_usedlen; int ir_buflen; void* ir_buf; } ;

/* Variables and functions */
 int flsl (int) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static int
isns_req_getspace(struct isns_req *req, uint32_t len)
{
	void *newbuf;
	int newlen;

	if (req->ir_usedlen + len <= req->ir_buflen)
		return (0);
	newlen = 1 << flsl(req->ir_usedlen + len);
	newbuf = realloc(req->ir_buf, newlen);
	if (newbuf == NULL) {
		log_err(1, "realloc");
		return (1);
	}
	req->ir_buf = newbuf;
	req->ir_buflen = newlen;
	return (0);
}