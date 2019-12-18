#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; scalar_t__ plan; scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_1__ addr; } ;
struct ccconn {TYPE_3__ calling; } ;
struct TYPE_5__ {scalar_t__ type; scalar_t__ plan; scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct ccaddr {TYPE_2__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_ISPRESENT (TYPE_3__) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
addr_matches(const struct ccaddr *addr, const struct ccconn *conn)
{

	if (!IE_ISPRESENT(conn->calling))
		return (0);

	return (addr->addr.type == conn->calling.addr.type &&
	    addr->addr.plan == conn->calling.addr.plan &&
	    addr->addr.len == conn->calling.addr.len &&
	    memcmp(addr->addr.addr, conn->calling.addr.addr,
	    addr->addr.len) == 0);
}