#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_4__ {size_t cur_sample; int /*<<< orphan*/  cur_seq; TYPE_2__* samples; } ;
struct TYPE_6__ {TYPE_1__ ah_chansurvey; } ;
struct TYPE_5__ {int /*<<< orphan*/  seq_num; } ;
typedef  int /*<<< orphan*/  HAL_SURVEY_SAMPLE ;
typedef  TYPE_1__ HAL_CHANNEL_SURVEY ;

/* Variables and functions */
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int CHANNEL_SURVEY_SAMPLE_COUNT ; 
 int /*<<< orphan*/  OS_MEMCPY (TYPE_2__*,int /*<<< orphan*/ *,int) ; 

void
ath_hal_survey_add_sample(struct ath_hal *ah, HAL_SURVEY_SAMPLE *hs)
{
	HAL_CHANNEL_SURVEY *cs;

	cs = &AH_PRIVATE(ah)->ah_chansurvey;

	OS_MEMCPY(&cs->samples[cs->cur_sample], hs, sizeof(*hs));
	cs->samples[cs->cur_sample].seq_num = cs->cur_seq;
	cs->cur_sample = (cs->cur_sample + 1) % CHANNEL_SURVEY_SAMPLE_COUNT;
	cs->cur_seq++;
}