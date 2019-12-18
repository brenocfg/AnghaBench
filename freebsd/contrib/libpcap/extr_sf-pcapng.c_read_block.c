#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct block_header {int block_type; int total_length; } ;
typedef  struct block_header u_char ;
struct pcap_ng_sf {int max_blocksize; } ;
struct block_trailer {int dummy; } ;
struct block_cursor {size_t data_remaining; int block_type; struct block_header* data; } ;
struct TYPE_3__ {int bufsize; void* buffer; scalar_t__ swapped; struct pcap_ng_sf* priv; } ;
typedef  TYPE_1__ pcap_t ;
typedef  int /*<<< orphan*/  bhdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ERRBUF_SIZE ; 
 void* SWAPLONG (int) ; 
 int /*<<< orphan*/  memcpy (void*,struct block_header*,int) ; 
 int /*<<< orphan*/  pcap_snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 
 int read_bytes (int /*<<< orphan*/ *,struct block_header*,size_t,int,char*) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static int
read_block(FILE *fp, pcap_t *p, struct block_cursor *cursor, char *errbuf)
{
	struct pcap_ng_sf *ps;
	int status;
	struct block_header bhdr;
	u_char *bdata;
	size_t data_remaining;

	ps = p->priv;

	status = read_bytes(fp, &bhdr, sizeof(bhdr), 0, errbuf);
	if (status <= 0)
		return (status);	/* error or EOF */

	if (p->swapped) {
		bhdr.block_type = SWAPLONG(bhdr.block_type);
		bhdr.total_length = SWAPLONG(bhdr.total_length);
	}

	/*
	 * Is this block "too big"?
	 *
	 * We choose 16MB as "too big", for now, so that we handle
	 * "reasonably" large buffers but don't chew up all the
	 * memory if we read a malformed file.
	 */
	if (bhdr.total_length > 16*1024*1024) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "pcapng block size %u > maximum %u",
		    bhdr.total_length, 16*1024*1024);
		    return (-1);
	}

	/*
	 * Is this block "too small" - i.e., is it shorter than a block
	 * header plus a block trailer?
	 */
	if (bhdr.total_length < sizeof(struct block_header) +
	    sizeof(struct block_trailer)) {
		pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE,
		    "block in pcapng dump file has a length of %u < %lu",
		    bhdr.total_length,
		    (unsigned long)(sizeof(struct block_header) + sizeof(struct block_trailer)));
		return (-1);
	}

	/*
	 * Is the buffer big enough?
	 */
	if (p->bufsize < bhdr.total_length) {
		/*
		 * No - make it big enough, unless it's too big.
		 */
		void *bigger_buffer;

		if (bhdr.total_length > ps->max_blocksize) {
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "block is larger than maximum block size %u",
			    ps->max_blocksize);
			return (-1);
		}
		bigger_buffer = realloc(p->buffer, bhdr.total_length);
		if (bigger_buffer == NULL) {
			pcap_snprintf(errbuf, PCAP_ERRBUF_SIZE, "out of memory");
			return (-1);
		}
		p->buffer = bigger_buffer;
	}

	/*
	 * Copy the stuff we've read to the buffer, and read the rest
	 * of the block.
	 */
	memcpy(p->buffer, &bhdr, sizeof(bhdr));
	bdata = (u_char *)p->buffer + sizeof(bhdr);
	data_remaining = bhdr.total_length - sizeof(bhdr);
	if (read_bytes(fp, bdata, data_remaining, 1, errbuf) == -1)
		return (-1);

	/*
	 * Initialize the cursor.
	 */
	cursor->data = bdata;
	cursor->data_remaining = data_remaining - sizeof(struct block_trailer);
	cursor->block_type = bhdr.block_type;
	return (1);
}