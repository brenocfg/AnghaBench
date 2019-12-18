#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct es_info {int ctrl; } ;
struct TYPE_2__ {scalar_t__ minspeed; scalar_t__ maxspeed; } ;
struct es_chinfo {scalar_t__ index; TYPE_1__ caps; struct es_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int CTRL_PCLKDIV ; 
 int CTRL_SH_PCLKDIV ; 
 int CTRL_SH_WTSRSEL ; 
 int CTRL_WTSRSEL ; 
 int DAC2_SRTODIV (scalar_t__) ; 
 int /*<<< orphan*/  ES1370_REG_CONTROL ; 
 scalar_t__ ES_DAC1 ; 
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 int /*<<< orphan*/  es_wr (struct es_info*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static uint32_t
eschan1370_setspeed(kobj_t obj, void *data, uint32_t speed)
{
	struct es_chinfo *ch = data;
	struct es_info *es = ch->parent;

	ES_LOCK(es);
	/* Fixed rate , do nothing. */
	if (ch->caps.minspeed == ch->caps.maxspeed) {
		ES_UNLOCK(es);
		return (ch->caps.maxspeed);
	}
	if (speed < ch->caps.minspeed)
		speed = ch->caps.minspeed;
	if (speed > ch->caps.maxspeed)
		speed = ch->caps.maxspeed;
	if (ch->index == ES_DAC1) {
		/*
		 * DAC1 does not support continuous rate settings.
		 * Pick the nearest and use it since FEEDER_RATE will
		 * do the proper conversion for us.
		 */
		es->ctrl &= ~CTRL_WTSRSEL;
		if (speed < 8268) {
			speed = 5512;
			es->ctrl |= 0 << CTRL_SH_WTSRSEL;
		} else if (speed < 16537) {
			speed = 11025;
			es->ctrl |= 1 << CTRL_SH_WTSRSEL;
		} else if (speed < 33075) {
			speed = 22050;
			es->ctrl |= 2 << CTRL_SH_WTSRSEL;
		} else {
			speed = 44100;
			es->ctrl |= 3 << CTRL_SH_WTSRSEL;
		}
	} else {
		es->ctrl &= ~CTRL_PCLKDIV;
		es->ctrl |= DAC2_SRTODIV(speed) << CTRL_SH_PCLKDIV;
	}
	es_wr(es, ES1370_REG_CONTROL, es->ctrl, 4);
	ES_UNLOCK(es);
	return (speed);
}