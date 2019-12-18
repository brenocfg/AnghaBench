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
struct sockaddr {int dummy; } ;
struct descr {int /*<<< orphan*/  s; int /*<<< orphan*/  __ss; struct sockaddr* sa; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct descr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_INVALID_SOCKET ; 

__attribute__((used)) static void
init_descr(struct descr *d)
{
    memset(d, 0, sizeof(*d));
    d->sa = (struct sockaddr *)&d->__ss;
    d->s = rk_INVALID_SOCKET;
}