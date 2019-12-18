#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  req ;
struct TYPE_2__ {int /*<<< orphan*/  dl_primitive; } ;
typedef  TYPE_1__ dl_info_req_t ;

/* Variables and functions */
 int /*<<< orphan*/  DL_INFO_REQ ; 
 int send_request (int,char*,int,char*,char*) ; 

__attribute__((used)) static int
dlinforeq(int fd, char *ebuf)
{
	dl_info_req_t req;

	req.dl_primitive = DL_INFO_REQ;

	return (send_request(fd, (char *)&req, sizeof(req), "info", ebuf));
}