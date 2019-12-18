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
struct exynos_ppmu {int /*<<< orphan*/  regmap; } ;
struct devfreq_event_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {unsigned int event_type; } ;

/* Variables and functions */
 int PPMU_CCNT_MASK ; 
 int PPMU_ENABLE ; 
 unsigned int PPMU_PMNC_CC_DIVIDER_MASK ; 
 unsigned int PPMU_PMNC_CC_RESET_MASK ; 
 int PPMU_PMNC_CC_RESET_SHIFT ; 
 unsigned int PPMU_PMNC_COUNTER_RESET_MASK ; 
 int PPMU_PMNC_COUNTER_RESET_SHIFT ; 
 unsigned int PPMU_PMNC_ENABLE_MASK ; 
 int PPMU_PMNC_ENABLE_SHIFT ; 
 int /*<<< orphan*/  PPMU_V2_CH_EVx_TYPE (int) ; 
 int /*<<< orphan*/  PPMU_V2_CNTENS ; 
 unsigned int PPMU_V2_MODE_MANUAL ; 
 int /*<<< orphan*/  PPMU_V2_PMNC ; 
 unsigned int PPMU_V2_PMNC_START_MODE_MASK ; 
 unsigned int PPMU_V2_PMNC_START_MODE_SHIFT ; 
 struct exynos_ppmu* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int exynos_ppmu_find_ppmu_id (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int exynos_ppmu_v2_set_event(struct devfreq_event_dev *edev)
{
	struct exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	unsigned int pmnc, cntens;
	int id = exynos_ppmu_find_ppmu_id(edev);
	int ret;

	/* Enable all counters */
	ret = regmap_read(info->regmap, PPMU_V2_CNTENS, &cntens);
	if (ret < 0)
		return ret;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_write(info->regmap, PPMU_V2_CNTENS, cntens);
	if (ret < 0)
		return ret;

	/* Set the event of proper data type monitoring */
	ret = regmap_write(info->regmap, PPMU_V2_CH_EVx_TYPE(id),
			   edev->desc->event_type);
	if (ret < 0)
		return ret;

	/* Reset cycle counter/performance counter and enable PPMU */
	ret = regmap_read(info->regmap, PPMU_V2_PMNC, &pmnc);
	if (ret < 0)
		return ret;

	pmnc &= ~(PPMU_PMNC_ENABLE_MASK
			| PPMU_PMNC_COUNTER_RESET_MASK
			| PPMU_PMNC_CC_RESET_MASK
			| PPMU_PMNC_CC_DIVIDER_MASK
			| PPMU_V2_PMNC_START_MODE_MASK);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_ENABLE_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_COUNTER_RESET_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_CC_RESET_SHIFT);
	pmnc |= (PPMU_V2_MODE_MANUAL << PPMU_V2_PMNC_START_MODE_SHIFT);

	ret = regmap_write(info->regmap, PPMU_V2_PMNC, pmnc);
	if (ret < 0)
		return ret;

	return 0;
}