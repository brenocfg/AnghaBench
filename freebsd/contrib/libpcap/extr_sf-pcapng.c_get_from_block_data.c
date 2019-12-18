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
struct block_cursor {size_t data_remaining; void* data; int /*<<< orphan*/  block_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
get_from_block_data(struct block_cursor *cursor, size_t chunk_size,
    char *errbuf)
{
	void *data;

	/*
	 * Make sure we have the specified amount of data remaining in
	 * the block data.
	 */
	if (cursor->data_remaining < chunk_size) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "block of type %u in pcapng dump file is too short",
		    cursor->block_type);
		return (NULL);
	}

	/*
	 * Return the current pointer, and skip past the chunk.
	 */
	data = cursor->data;
	cursor->data += chunk_size;
	cursor->data_remaining -= chunk_size;
	return (data);
}