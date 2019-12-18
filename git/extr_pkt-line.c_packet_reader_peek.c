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
struct packet_reader {int line_peeked; int status; } ;
typedef  enum packet_read_status { ____Placeholder_packet_read_status } packet_read_status ;

/* Variables and functions */
 int /*<<< orphan*/  packet_reader_read (struct packet_reader*) ; 

enum packet_read_status packet_reader_peek(struct packet_reader *reader)
{
	/* Only allow peeking a single line */
	if (reader->line_peeked)
		return reader->status;

	/* Peek a line by reading it and setting peeked flag */
	packet_reader_read(reader);
	reader->line_peeked = 1;
	return reader->status;
}