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
struct TYPE_2__ {int dl_max_conind; int /*<<< orphan*/  dl_sap; int /*<<< orphan*/  dl_service_mode; int /*<<< orphan*/  dl_primitive; } ;
typedef  TYPE_1__ dl_bind_req_t ;
typedef  int /*<<< orphan*/  bpf_u_int32 ;

/* Variables and functions */
 int /*<<< orphan*/  DL_BIND_REQ ; 
 int /*<<< orphan*/  DL_CLDLS ; 
 int /*<<< orphan*/  DL_HP_RAWDLS ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int send_request (int,char*,int,char*,char*) ; 

__attribute__((used)) static int
dlbindreq(int fd, bpf_u_int32 sap, char *ebuf)
{

	dl_bind_req_t	req;

	memset((char *)&req, 0, sizeof(req));
	req.dl_primitive = DL_BIND_REQ;
	/* XXX - what if neither of these are defined? */
#if defined(DL_HP_RAWDLS)
	req.dl_max_conind = 1;			/* XXX magic number */
	req.dl_service_mode = DL_HP_RAWDLS;
#elif defined(DL_CLDLS)
	req.dl_service_mode = DL_CLDLS;
#endif
	req.dl_sap = sap;

	return (send_request(fd, (char *)&req, sizeof(req), "bind", ebuf));
}