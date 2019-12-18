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
typedef  scalar_t__ uint32_t ;
struct es_info {int dummy; } ;
struct es_chinfo {scalar_t__ dir; int /*<<< orphan*/  index; struct es_info* parent; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 int /*<<< orphan*/  ES_LOCK (struct es_info*) ; 
 int /*<<< orphan*/  ES_UNLOCK (struct es_info*) ; 
 scalar_t__ PCMDIR_PLAY ; 
 scalar_t__ es1371_adc_rate (struct es_info*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ es1371_dac_rate (struct es_info*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
eschan1371_setspeed(kobj_t obj, void *data, uint32_t speed)
{
  	struct es_chinfo *ch = data;
  	struct es_info *es = ch->parent;
	uint32_t i;
	int delta;

	ES_LOCK(es);
	if (ch->dir == PCMDIR_PLAY)
  		i = es1371_dac_rate(es, speed, ch->index); /* play */
	else
  		i = es1371_adc_rate(es, speed, ch->index); /* record */
	ES_UNLOCK(es);
	delta = (speed > i) ? (speed - i) : (i - speed);
	if (delta < 2)
		return (speed);
	return (i);
}