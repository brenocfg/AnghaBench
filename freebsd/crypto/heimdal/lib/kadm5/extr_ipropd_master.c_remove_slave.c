#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__ ac; struct TYPE_5__* name; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ slave ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  krb5_auth_con_free (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rk_IS_BAD_SOCKET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rk_closesocket (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_slave (krb5_context context, slave *s, slave **root)
{
    slave **p;

    if (!rk_IS_BAD_SOCKET(s->fd))
	rk_closesocket (s->fd);
    if (s->name)
	free (s->name);
    if (s->ac)
	krb5_auth_con_free (context, s->ac);

    for (p = root; *p; p = &(*p)->next)
	if (*p == s) {
	    *p = s->next;
	    break;
	}
    free (s);
}