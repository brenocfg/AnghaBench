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
struct of_device_id {struct cppi_glue_infos const* data; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct cppi_glue_infos {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cppi41_dma_ids ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct cppi_glue_infos *get_glue_info(struct device *dev)
{
	const struct of_device_id *of_id;

	of_id = of_match_node(cppi41_dma_ids, dev->of_node);
	if (!of_id)
		return NULL;
	return of_id->data;
}