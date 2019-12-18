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
struct regmap {int dummy; } ;
struct mrfld_extcon_data {unsigned int status; struct regmap* regmap; } ;

/* Variables and functions */
 unsigned int BCOVE_CHGRIRQ_USBIDDET ; 
 int /*<<< orphan*/  BCOVE_SCHGRIRQ1 ; 
 int ENODATA ; 
 int mrfld_extcon_role_detect (struct mrfld_extcon_data*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int mrfld_extcon_cable_detect(struct mrfld_extcon_data *data)
{
	struct regmap *regmap = data->regmap;
	unsigned int status, change;
	int ret;

	/*
	 * It seems SCU firmware clears the content of BCOVE_CHGRIRQ1
	 * and makes it useless for OS. Instead we compare a previously
	 * stored status to the current one, provided by BCOVE_SCHGRIRQ1.
	 */
	ret = regmap_read(regmap, BCOVE_SCHGRIRQ1, &status);
	if (ret)
		return ret;

	change = status ^ data->status;
	if (!change)
		return -ENODATA;

	if (change & BCOVE_CHGRIRQ_USBIDDET) {
		ret = mrfld_extcon_role_detect(data);
		if (ret)
			return ret;
	}

	data->status = status;

	return 0;
}