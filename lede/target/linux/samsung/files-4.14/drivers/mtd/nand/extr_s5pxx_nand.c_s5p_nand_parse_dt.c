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
struct s5p_nand_host {int cpu_type; } ;
struct device {int dummy; } ;
typedef  enum s5p_cpu_type { ____Placeholder_s5p_cpu_type } s5p_cpu_type ;

/* Variables and functions */
 scalar_t__ of_device_get_match_data (struct device*) ; 

__attribute__((used)) static void s5p_nand_parse_dt(struct s5p_nand_host *host, struct device *dev)
{
	host->cpu_type = (enum s5p_cpu_type)of_device_get_match_data(dev);
}