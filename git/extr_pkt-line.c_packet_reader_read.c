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
struct strbuf {int dummy; } ;
struct packet_reader {int status; int /*<<< orphan*/ * line; int /*<<< orphan*/ * buffer; scalar_t__ use_sideband; int /*<<< orphan*/  pktlen; int /*<<< orphan*/  me; int /*<<< orphan*/  options; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  src_len; int /*<<< orphan*/  src_buffer; int /*<<< orphan*/  fd; scalar_t__ line_peeked; } ;
typedef  enum sideband_type { ____Placeholder_sideband_type } sideband_type ;
typedef  enum packet_read_status { ____Placeholder_packet_read_status } packet_read_status ;

/* Variables and functions */
 scalar_t__ PACKET_READ_NORMAL ; 
 struct strbuf STRBUF_INIT ; 
 scalar_t__ demultiplex_sideband (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct strbuf*,int*) ; 
 int packet_read_with_status (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum packet_read_status packet_reader_read(struct packet_reader *reader)
{
	struct strbuf scratch = STRBUF_INIT;

	if (reader->line_peeked) {
		reader->line_peeked = 0;
		return reader->status;
	}

	/*
	 * Consume all progress packets until a primary payload packet is
	 * received
	 */
	while (1) {
		enum sideband_type sideband_type;
		reader->status = packet_read_with_status(reader->fd,
							 &reader->src_buffer,
							 &reader->src_len,
							 reader->buffer,
							 reader->buffer_size,
							 &reader->pktlen,
							 reader->options);
		if (!reader->use_sideband)
			break;
		if (demultiplex_sideband(reader->me, reader->buffer,
					 reader->pktlen, 1, &scratch,
					 &sideband_type))
			break;
	}

	if (reader->status == PACKET_READ_NORMAL)
		/* Skip the sideband designator if sideband is used */
		reader->line = reader->use_sideband ?
			reader->buffer + 1 : reader->buffer;
	else
		reader->line = NULL;

	return reader->status;
}