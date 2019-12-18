#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sa_family; } ;
struct TYPE_7__ {TYPE_1__ sa; } ;
struct TYPE_8__ {TYPE_2__ type; } ;
typedef  TYPE_3__ isc_sockaddr_t ;
typedef  int /*<<< orphan*/  isc_netaddr_t ;
typedef  int /*<<< orphan*/  isc_boolean_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  isc_netaddr_fromsockaddr (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int /*<<< orphan*/  isc_netaddr_isexperimental (int /*<<< orphan*/ *) ; 

isc_boolean_t
isc_sockaddr_isexperimental(const isc_sockaddr_t *sockaddr) {
	isc_netaddr_t netaddr;

	if (sockaddr->type.sa.sa_family == AF_INET) {
		isc_netaddr_fromsockaddr(&netaddr, sockaddr);
		return (isc_netaddr_isexperimental(&netaddr));
	}
	return (ISC_FALSE);
}