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
struct au_info {int* z; int* y; int* x; int /*<<< orphan*/  routes; } ;

/* Variables and functions */
 scalar_t__ AU_REG_RTBASE ; 
 int au_rd (struct au_info*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  au_setbit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  au_wr (struct au_info*,int /*<<< orphan*/ ,scalar_t__,int,int) ; 

__attribute__((used)) static void
au_delroute(struct au_info *au, int route)
{
	int i;
	int j=au->z[route];

	au_setbit(au->routes, route, 0);
	au->z[route]=0x1f;
	i=au_rd(au, 0, AU_REG_RTBASE+(route<<2), 4);
	au_wr(au, 0, AU_REG_RTBASE+(au->y[route]<<2), i, 4);
	au->y[i & 0x7f]=au->y[route];
	au_wr(au, 0, AU_REG_RTBASE+(route<<2), 0xfffffffe, 4);
	if (au->x[j] == route) au->x[j]=au->y[route];
	au->y[route]=0x7f;
}