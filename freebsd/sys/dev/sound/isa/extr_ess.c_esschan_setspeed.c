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
typedef  int /*<<< orphan*/  u_int32_t ;
struct ess_info {scalar_t__ newspeed; } ;
struct ess_chinfo {int /*<<< orphan*/  spd; struct ess_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ess_calcspeed8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ess_calcspeed9 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_int32_t
esschan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct ess_chinfo *ch = data;
	struct ess_info *sc = ch->parent;

	ch->spd = speed;
	if (sc->newspeed)
		ess_calcspeed9(&ch->spd);
	else
		ess_calcspeed8(&ch->spd);
	return ch->spd;
}