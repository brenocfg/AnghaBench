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
struct isns_req {int ir_buflen; int /*<<< orphan*/ * ir_buf; scalar_t__ ir_usedlen; } ;
struct isns_hdr {int dummy; } ;

/* Variables and functions */
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct isns_req*) ; 
 int /*<<< orphan*/  log_err (int,char*) ; 

struct isns_req *
isns_req_alloc(void)
{
	struct isns_req *req;

	req = calloc(sizeof(struct isns_req), 1);
	if (req == NULL) {
		log_err(1, "calloc");
		return (NULL);
	}
	req->ir_buflen = sizeof(struct isns_hdr);
	req->ir_usedlen = 0;
	req->ir_buf = calloc(req->ir_buflen, 1);
	if (req->ir_buf == NULL) {
		free(req);
		log_err(1, "calloc");
		return (NULL);
	}
	return (req);
}