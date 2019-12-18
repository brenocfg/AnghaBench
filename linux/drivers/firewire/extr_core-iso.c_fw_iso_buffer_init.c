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
struct fw_iso_buffer {int dummy; } ;
struct fw_card {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int fw_iso_buffer_alloc (struct fw_iso_buffer*,int) ; 
 int /*<<< orphan*/  fw_iso_buffer_destroy (struct fw_iso_buffer*,struct fw_card*) ; 
 int fw_iso_buffer_map_dma (struct fw_iso_buffer*,struct fw_card*,int) ; 

int fw_iso_buffer_init(struct fw_iso_buffer *buffer, struct fw_card *card,
		       int page_count, enum dma_data_direction direction)
{
	int ret;

	ret = fw_iso_buffer_alloc(buffer, page_count);
	if (ret < 0)
		return ret;

	ret = fw_iso_buffer_map_dma(buffer, card, direction);
	if (ret < 0)
		fw_iso_buffer_destroy(buffer, card);

	return ret;
}