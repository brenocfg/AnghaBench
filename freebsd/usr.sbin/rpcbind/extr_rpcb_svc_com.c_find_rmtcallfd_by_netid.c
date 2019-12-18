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
struct rmtcallfd_list {int fd; int /*<<< orphan*/  netid; struct rmtcallfd_list* next; } ;

/* Variables and functions */
 struct rmtcallfd_list* rmthead ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
find_rmtcallfd_by_netid(char *netid)
{
	struct rmtcallfd_list *rmt;

	for (rmt = rmthead; rmt != NULL; rmt = rmt->next) {
		if (strcmp(netid, rmt->netid) == 0) {
			return (rmt->fd);
		}
	}
	return (-1);
}