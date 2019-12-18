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
struct isns_req {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isns_req_add (struct isns_req*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
isns_req_add_delim(struct isns_req *req)
{

	isns_req_add(req, 0, 0, NULL);
}