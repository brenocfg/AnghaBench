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
struct isns_req {int ir_usedlen; int /*<<< orphan*/ * ir_buf; } ;
struct isns_hdr {int dummy; } ;

/* Variables and functions */
 int be32dec (int /*<<< orphan*/ *) ; 

uint32_t
isns_req_get_status(struct isns_req *req)
{

	if (req->ir_usedlen < sizeof(struct isns_hdr) + 4)
		return (-1);
	return (be32dec(&req->ir_buf[sizeof(struct isns_hdr)]));
}