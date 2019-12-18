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
struct mac {int dummy; } ;
typedef  int socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PEERLABEL ; 
 int getsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mac*,int*) ; 

int
mac_get_peer(int fd, struct mac *label)
{
	socklen_t len;

	len = sizeof(*label);
	return (getsockopt(fd, SOL_SOCKET, SO_PEERLABEL, label, &len));
}