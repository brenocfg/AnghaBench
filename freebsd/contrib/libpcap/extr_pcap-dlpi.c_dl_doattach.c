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
struct TYPE_2__ {int dl_ppa; int /*<<< orphan*/  dl_primitive; } ;
typedef  TYPE_1__ dl_attach_req_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  DL_ATTACH_REQ ; 
 int MAXDLBUF ; 
 int PCAP_ERROR ; 
 int dlokack (int,char*,char*,char*) ; 
 scalar_t__ send_request (int,char*,int,char*,char*) ; 

__attribute__((used)) static int
dl_doattach(int fd, int ppa, char *ebuf)
{
	dl_attach_req_t	req;
	bpf_u_int32 buf[MAXDLBUF];
	int err;

	req.dl_primitive = DL_ATTACH_REQ;
	req.dl_ppa = ppa;
	if (send_request(fd, (char *)&req, sizeof(req), "attach", ebuf) < 0)
		return (PCAP_ERROR);

	err = dlokack(fd, "attach", (char *)buf, ebuf);
	if (err < 0)
		return (err);
	return (0);
}