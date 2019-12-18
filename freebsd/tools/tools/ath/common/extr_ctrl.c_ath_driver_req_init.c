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
struct ath_driver_req {int s; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct ath_driver_req*,int) ; 

int
ath_driver_req_init(struct ath_driver_req *req)
{

	bzero(req, sizeof(*req));
	req->s = -1;
	return (0);
}