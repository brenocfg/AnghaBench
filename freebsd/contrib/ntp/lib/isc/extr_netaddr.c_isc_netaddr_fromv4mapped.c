#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  in6; int /*<<< orphan*/  in; } ;
struct TYPE_9__ {scalar_t__ family; TYPE_1__ type; } ;
typedef  TYPE_2__ isc_netaddr_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  DE_CONST (TYPE_2__ const*,TYPE_2__*) ; 
 int IN6_IS_ADDR_V4MAPPED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void
isc_netaddr_fromv4mapped(isc_netaddr_t *t, const isc_netaddr_t *s) {
	isc_netaddr_t *src;

	DE_CONST(s, src);	/* Must come before IN6_IS_ADDR_V4MAPPED. */

	REQUIRE(s->family == AF_INET6);
	REQUIRE(IN6_IS_ADDR_V4MAPPED(&src->type.in6));

	memset(t, 0, sizeof(*t));
	t->family = AF_INET;
	memcpy(&t->type.in, (char *)&src->type.in6 + 12, 4);
	return;
}