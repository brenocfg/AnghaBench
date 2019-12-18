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
struct sec_request {int /*<<< orphan*/  req_base; int /*<<< orphan*/  (* cb ) (struct sec_bd_info*,int /*<<< orphan*/ ) ;} ;
struct sec_bd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct sec_bd_info*,int /*<<< orphan*/ ) ; 

void sec_alg_callback(struct sec_bd_info *resp, void *shadow)
{
	struct sec_request *sec_req = shadow;

	sec_req->cb(resp, sec_req->req_base);
}