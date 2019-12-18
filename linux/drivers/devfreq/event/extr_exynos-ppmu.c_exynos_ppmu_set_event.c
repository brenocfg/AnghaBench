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
typedef  int u32 ;
struct exynos_ppmu {int /*<<< orphan*/  regmap; } ;
struct devfreq_event_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {int event_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPMU_BEVTxSEL (int) ; 
 int PPMU_CCNT_MASK ; 
 int /*<<< orphan*/  PPMU_CNTENS ; 
 int PPMU_ENABLE ; 
 int /*<<< orphan*/  PPMU_PMNC ; 
 int PPMU_PMNC_CC_RESET_MASK ; 
 int PPMU_PMNC_CC_RESET_SHIFT ; 
 int PPMU_PMNC_COUNTER_RESET_MASK ; 
 int PPMU_PMNC_COUNTER_RESET_SHIFT ; 
 int PPMU_PMNC_ENABLE_MASK ; 
 int PPMU_PMNC_ENABLE_SHIFT ; 
 struct exynos_ppmu* devfreq_event_get_drvdata (struct devfreq_event_dev*) ; 
 int exynos_ppmu_find_ppmu_id (struct devfreq_event_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int exynos_ppmu_set_event(struct devfreq_event_dev *edev)
{
	struct exynos_ppmu *info = devfreq_event_get_drvdata(edev);
	int id = exynos_ppmu_find_ppmu_id(edev);
	int ret;
	u32 pmnc, cntens;

	if (id < 0)
		return id;

	/* Enable specific counter */
	ret = regmap_read(info->regmap, PPMU_CNTENS, &cntens);
	if (ret < 0)
		return ret;

	cntens |= (PPMU_CCNT_MASK | (PPMU_ENABLE << id));
	ret = regmap_write(info->regmap, PPMU_CNTENS, cntens);
	if (ret < 0)
		return ret;

	/* Set the event of proper data type monitoring */
	ret = regmap_write(info->regmap, PPMU_BEVTxSEL(id),
			   edev->desc->event_type);
	if (ret < 0)
		return ret;

	/* Reset cycle counter/performance counter and enable PPMU */
	ret = regmap_read(info->regmap, PPMU_PMNC, &pmnc);
	if (ret < 0)
		return ret;

	pmnc &= ~(PPMU_PMNC_ENABLE_MASK
			| PPMU_PMNC_COUNTER_RESET_MASK
			| PPMU_PMNC_CC_RESET_MASK);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_ENABLE_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_COUNTER_RESET_SHIFT);
	pmnc |= (PPMU_ENABLE << PPMU_PMNC_CC_RESET_SHIFT);
	ret = regmap_write(info->regmap, PPMU_PMNC, pmnc);
	if (ret < 0)
		return ret;

	return 0;
}