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
struct rpc_state {int alloc; int len; char* buf; scalar_t__ write_line_lengths; int /*<<< orphan*/  out; } ;
typedef  enum packet_read_status { ____Placeholder_packet_read_status } packet_read_status ;

/* Variables and functions */
 size_t LARGE_PACKET_MAX ; 
#define  PACKET_READ_DELIM 131 
#define  PACKET_READ_EOF 130 
#define  PACKET_READ_FLUSH 129 
 int PACKET_READ_GENTLE_ON_EOF ; 
#define  PACKET_READ_NORMAL 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int packet_read_with_status (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,size_t,int*,int) ; 
 int /*<<< orphan*/  set_packet_header (char*,size_t) ; 

__attribute__((used)) static int rpc_read_from_out(struct rpc_state *rpc, int options,
			     size_t *appended,
			     enum packet_read_status *status) {
	size_t left;
	char *buf;
	int pktlen_raw;

	if (rpc->write_line_lengths) {
		left = rpc->alloc - rpc->len - 4;
		buf = rpc->buf + rpc->len + 4;
	} else {
		left = rpc->alloc - rpc->len;
		buf = rpc->buf + rpc->len;
	}

	if (left < LARGE_PACKET_MAX)
		return 0;

	*status = packet_read_with_status(rpc->out, NULL, NULL, buf,
			left, &pktlen_raw, options);
	if (*status != PACKET_READ_EOF) {
		*appended = pktlen_raw + (rpc->write_line_lengths ? 4 : 0);
		rpc->len += *appended;
	}

	if (rpc->write_line_lengths) {
		switch (*status) {
		case PACKET_READ_EOF:
			if (!(options & PACKET_READ_GENTLE_ON_EOF))
				die(_("shouldn't have EOF when not gentle on EOF"));
			break;
		case PACKET_READ_NORMAL:
			set_packet_header(buf - 4, *appended);
			break;
		case PACKET_READ_DELIM:
			memcpy(buf - 4, "0001", 4);
			break;
		case PACKET_READ_FLUSH:
			memcpy(buf - 4, "0000", 4);
			break;
		}
	}

	return 1;
}