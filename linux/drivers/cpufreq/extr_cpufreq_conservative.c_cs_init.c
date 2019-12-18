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
struct dbs_data {struct cs_dbs_tuners* tuners; scalar_t__ ignore_nice_load; int /*<<< orphan*/  sampling_down_factor; int /*<<< orphan*/  up_threshold; } ;
struct cs_dbs_tuners {int /*<<< orphan*/  freq_step; int /*<<< orphan*/  down_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEF_FREQUENCY_DOWN_THRESHOLD ; 
 int /*<<< orphan*/  DEF_FREQUENCY_STEP ; 
 int /*<<< orphan*/  DEF_FREQUENCY_UP_THRESHOLD ; 
 int /*<<< orphan*/  DEF_SAMPLING_DOWN_FACTOR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct cs_dbs_tuners* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs_init(struct dbs_data *dbs_data)
{
	struct cs_dbs_tuners *tuners;

	tuners = kzalloc(sizeof(*tuners), GFP_KERNEL);
	if (!tuners)
		return -ENOMEM;

	tuners->down_threshold = DEF_FREQUENCY_DOWN_THRESHOLD;
	tuners->freq_step = DEF_FREQUENCY_STEP;
	dbs_data->up_threshold = DEF_FREQUENCY_UP_THRESHOLD;
	dbs_data->sampling_down_factor = DEF_SAMPLING_DOWN_FACTOR;
	dbs_data->ignore_nice_load = 0;
	dbs_data->tuners = tuners;

	return 0;
}