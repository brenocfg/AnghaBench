#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_3__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int s_addr; } ;
struct TYPE_7__ {TYPE_1__ sin_addr; } ;
struct nbns_rq {int nr_fd; int nr_flags; TYPE_5__* nr_if; TYPE_2__ nr_dest; } ;
typedef  int /*<<< orphan*/  opt ;
typedef  int /*<<< orphan*/  locaddr ;
struct TYPE_9__ {int s_addr; } ;
struct TYPE_10__ {TYPE_4__ id_mask; TYPE_3__ id_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int NBERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NBERR_NOBCASTIFS ; 
 int NBRQF_BROADCAST ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int errno ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nbns_rq_opensocket(struct nbns_rq *rqp)
{
	struct sockaddr_in locaddr;
	int opt, s;

	s = rqp->nr_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (s < 0)
		return errno;
	if (rqp->nr_flags & NBRQF_BROADCAST) {
		opt = 1;
		if (setsockopt(s, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt)) < 0)
			return errno;
		if (rqp->nr_if == NULL)
			return NBERROR(NBERR_NOBCASTIFS);
		bzero(&locaddr, sizeof(locaddr));
		locaddr.sin_family = AF_INET;
		locaddr.sin_len = sizeof(locaddr);
		locaddr.sin_addr = rqp->nr_if->id_addr;
		rqp->nr_dest.sin_addr.s_addr = rqp->nr_if->id_addr.s_addr | ~rqp->nr_if->id_mask.s_addr;
		if (bind(s, (struct sockaddr*)&locaddr, sizeof(locaddr)) < 0)
			return errno;
	}
	return 0;
}