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
struct mtx {int dummy; } ;
struct callout {int flags; struct mtx* mtx; } ;

/* Variables and functions */
 int CALLOUT_RETURNUNLOCKED ; 
 struct mtx Giant ; 
 int /*<<< orphan*/  memset (struct callout*,int /*<<< orphan*/ ,int) ; 

void
callout_init_mtx(struct callout *c, struct mtx *mtx, int flags)
{
	memset(c, 0, sizeof(*c));

	if (mtx == NULL)
		mtx = &Giant;

	c->mtx = mtx;
	c->flags = (flags & CALLOUT_RETURNUNLOCKED);
}