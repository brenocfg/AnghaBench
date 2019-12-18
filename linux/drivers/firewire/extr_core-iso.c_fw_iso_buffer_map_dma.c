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
struct fw_iso_buffer {int direction; int page_count; int page_count_mapped; int /*<<< orphan*/ * pages; } ;
struct fw_card {int /*<<< orphan*/  device; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_map_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_private (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fw_iso_buffer_map_dma(struct fw_iso_buffer *buffer, struct fw_card *card,
			  enum dma_data_direction direction)
{
	dma_addr_t address;
	int i;

	buffer->direction = direction;

	for (i = 0; i < buffer->page_count; i++) {
		address = dma_map_page(card->device, buffer->pages[i],
				       0, PAGE_SIZE, direction);
		if (dma_mapping_error(card->device, address))
			break;

		set_page_private(buffer->pages[i], address);
	}
	buffer->page_count_mapped = i;
	if (i < buffer->page_count)
		return -ENOMEM;

	return 0;
}