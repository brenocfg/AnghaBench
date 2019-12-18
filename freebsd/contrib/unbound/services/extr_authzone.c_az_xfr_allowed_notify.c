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
struct sockaddr_storage {int dummy; } ;
struct auth_xfer {struct auth_master* allow_notify_list; } ;
struct auth_master {struct auth_master* next; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ addr_matches_master (struct auth_master*,struct sockaddr_storage*,int /*<<< orphan*/ ,struct auth_master**) ; 

__attribute__((used)) static int
az_xfr_allowed_notify(struct auth_xfer* xfr, struct sockaddr_storage* addr,
	socklen_t addrlen, struct auth_master** fromhost)
{
	struct auth_master* p;
	for(p=xfr->allow_notify_list; p; p=p->next) {
		if(addr_matches_master(p, addr, addrlen, fromhost)) {
			return 1;
		}
	}
	return 0;
}