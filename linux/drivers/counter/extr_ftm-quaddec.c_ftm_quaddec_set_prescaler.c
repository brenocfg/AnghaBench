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
struct ftm_quaddec {int /*<<< orphan*/  ftm_quaddec_mutex; } ;
struct counter_device {struct ftm_quaddec* priv; } ;
struct counter_count {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FTM_FIELD_UPDATE (struct ftm_quaddec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  FTM_SC ; 
 int /*<<< orphan*/  FTM_SC_PS_MASK ; 
 int /*<<< orphan*/  ftm_clear_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_reset_counter (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  ftm_set_write_protection (struct ftm_quaddec*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ftm_quaddec_set_prescaler(struct counter_device *counter,
				     struct counter_count *count,
				     size_t cnt_mode)
{
	struct ftm_quaddec *ftm = counter->priv;

	mutex_lock(&ftm->ftm_quaddec_mutex);

	ftm_clear_write_protection(ftm);
	FTM_FIELD_UPDATE(ftm, FTM_SC, FTM_SC_PS_MASK, cnt_mode);
	ftm_set_write_protection(ftm);

	/* Also resets the counter as it is undefined anyway now */
	ftm_reset_counter(ftm);

	mutex_unlock(&ftm->ftm_quaddec_mutex);
	return 0;
}