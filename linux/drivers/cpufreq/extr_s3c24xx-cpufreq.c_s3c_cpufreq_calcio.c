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
struct s3c_cpufreq_config {TYPE_1__* info; } ;
struct TYPE_2__ {int (* calc_iotiming ) (struct s3c_cpufreq_config*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  s3c24xx_iotiming ; 
 int stub1 (struct s3c_cpufreq_config*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int s3c_cpufreq_calcio(struct s3c_cpufreq_config *cfg)
{
	if (cfg->info->calc_iotiming)
		return (cfg->info->calc_iotiming)(cfg, &s3c24xx_iotiming);

	return 0;
}