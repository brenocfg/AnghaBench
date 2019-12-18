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
struct ath_driver_req {int s; int /*<<< orphan*/ * ifname; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
ath_driver_req_close(struct ath_driver_req *req)
{
	if (req->s == -1)
		return (0);
	close(req->s);
	free(req->ifname);
	req->s = -1;
	req->ifname = NULL;
	return (0);
}