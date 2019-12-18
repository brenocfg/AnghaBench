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
typedef  enum packet_read_status { ____Placeholder_packet_read_status } packet_read_status ;

/* Variables and functions */
 int PACKET_READ_CHOMP_NEWLINE ; 
 int PACKET_READ_DELIM ; 
 int PACKET_READ_DIE_ON_ERR_PACKET ; 
 int PACKET_READ_EOF ; 
 int PACKET_READ_FLUSH ; 
 int PACKET_READ_NORMAL ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 scalar_t__ get_packet_data (int,char**,size_t*,char*,int,int) ; 
 int packet_length (char*) ; 
 int /*<<< orphan*/  packet_trace (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ starts_with (char*,char*) ; 

enum packet_read_status packet_read_with_status(int fd, char **src_buffer,
						size_t *src_len, char *buffer,
						unsigned size, int *pktlen,
						int options)
{
	int len;
	char linelen[4];

	if (get_packet_data(fd, src_buffer, src_len, linelen, 4, options) < 0) {
		*pktlen = -1;
		return PACKET_READ_EOF;
	}

	len = packet_length(linelen);

	if (len < 0) {
		die(_("protocol error: bad line length character: %.4s"), linelen);
	} else if (!len) {
		packet_trace("0000", 4, 0);
		*pktlen = 0;
		return PACKET_READ_FLUSH;
	} else if (len == 1) {
		packet_trace("0001", 4, 0);
		*pktlen = 0;
		return PACKET_READ_DELIM;
	} else if (len < 4) {
		die(_("protocol error: bad line length %d"), len);
	}

	len -= 4;
	if ((unsigned)len >= size)
		die(_("protocol error: bad line length %d"), len);

	if (get_packet_data(fd, src_buffer, src_len, buffer, len, options) < 0) {
		*pktlen = -1;
		return PACKET_READ_EOF;
	}

	if ((options & PACKET_READ_CHOMP_NEWLINE) &&
	    len && buffer[len-1] == '\n')
		len--;

	buffer[len] = 0;
	packet_trace(buffer, len, 0);

	if ((options & PACKET_READ_DIE_ON_ERR_PACKET) &&
	    starts_with(buffer, "ERR "))
		die(_("remote error: %s"), buffer + 4);

	*pktlen = len;
	return PACKET_READ_NORMAL;
}