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
struct packet_reader {int /*<<< orphan*/  line; } ;
typedef  enum protocol_version { ____Placeholder_protocol_version } protocol_version ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  PACKET_READ_DELIM 135 
#define  PACKET_READ_EOF 134 
#define  PACKET_READ_FLUSH 133 
#define  PACKET_READ_NORMAL 132 
 int determine_protocol_version_client (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die_initial_contact (int /*<<< orphan*/ ) ; 
 int packet_reader_peek (struct packet_reader*) ; 
 int /*<<< orphan*/  packet_reader_read (struct packet_reader*) ; 
 int /*<<< orphan*/  process_capabilities_v2 (struct packet_reader*) ; 
#define  protocol_unknown_version 131 
#define  protocol_v0 130 
#define  protocol_v1 129 
#define  protocol_v2 128 

enum protocol_version discover_version(struct packet_reader *reader)
{
	enum protocol_version version = protocol_unknown_version;

	/*
	 * Peek the first line of the server's response to
	 * determine the protocol version the server is speaking.
	 */
	switch (packet_reader_peek(reader)) {
	case PACKET_READ_EOF:
		die_initial_contact(0);
	case PACKET_READ_FLUSH:
	case PACKET_READ_DELIM:
		version = protocol_v0;
		break;
	case PACKET_READ_NORMAL:
		version = determine_protocol_version_client(reader->line);
		break;
	}

	switch (version) {
	case protocol_v2:
		process_capabilities_v2(reader);
		break;
	case protocol_v1:
		/* Read the peeked version line */
		packet_reader_read(reader);
		break;
	case protocol_v0:
		break;
	case protocol_unknown_version:
		BUG("unknown protocol version");
	}

	return version;
}