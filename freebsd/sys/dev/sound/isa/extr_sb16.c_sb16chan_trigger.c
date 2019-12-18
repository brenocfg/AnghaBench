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
struct sb_info {int dummy; } ;
struct sb_chinfo {int run; struct sb_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCMTRIG_COMMON (int) ; 
 int PCMTRIG_START ; 
 int /*<<< orphan*/  sb_setup (struct sb_info*) ; 

__attribute__((used)) static int
sb16chan_trigger(kobj_t obj, void *data, int go)
{
	struct sb_chinfo *ch = data;
	struct sb_info *sb = ch->parent;

	if (!PCMTRIG_COMMON(go))
		return 0;

	if (go == PCMTRIG_START)
		ch->run = 1;
	else
		ch->run = 0;

	sb_setup(sb);

	return 0;
}