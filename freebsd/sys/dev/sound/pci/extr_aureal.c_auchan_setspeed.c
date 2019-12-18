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
typedef  int u_int32_t ;
struct au_chinfo {scalar_t__ dir; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 scalar_t__ PCMDIR_PLAY ; 

__attribute__((used)) static int
auchan_setspeed(kobj_t obj, void *data, u_int32_t speed)
{
	struct au_chinfo *ch = data;
	if (ch->dir == PCMDIR_PLAY) {
	} else {
	}
	return speed;
}