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
typedef  int uint32_t ;
struct via_info {int codec_caps; int /*<<< orphan*/  codec; } ;
struct via_chinfo {struct via_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int AC97_EXTCAP_VRA ; 
 int /*<<< orphan*/  AC97_REGEXT_FDACRATE ; 
 int ac97_setrate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint32_t
via8233msgd_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct via_chinfo *ch = data;
	struct via_info *via = ch->parent;

	if (via->codec_caps & AC97_EXTCAP_VRA)
		return (ac97_setrate(via->codec, AC97_REGEXT_FDACRATE, speed));

	return (48000);
}