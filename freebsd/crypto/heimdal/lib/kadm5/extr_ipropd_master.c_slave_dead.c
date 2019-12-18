#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  fd; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ slave ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  SLAVE_F_DEAD ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_INVALID_SOCKET ; 
 int /*<<< orphan*/  rk_IS_BAD_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_closesocket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  slave_seen (TYPE_1__*) ; 

__attribute__((used)) static void
slave_dead(krb5_context context, slave *s)
{
    krb5_warnx(context, "slave %s dead", s->name);

    if (!rk_IS_BAD_SOCKET(s->fd)) {
	rk_closesocket (s->fd);
	s->fd = rk_INVALID_SOCKET;
    }
    s->flags |= SLAVE_F_DEAD;
    slave_seen(s);
}