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
struct rpc_state {size_t len; size_t pos; int flush_read_but_not_sent; size_t buf; scalar_t__ initial_buffer; } ;
typedef  enum packet_read_status { ____Placeholder_packet_read_status } packet_read_status ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int PACKET_READ_FLUSH ; 
 int /*<<< orphan*/  memcpy (void*,size_t,size_t) ; 
 int /*<<< orphan*/  rpc_read_from_out (struct rpc_state*,int /*<<< orphan*/ ,size_t*,int*) ; 

__attribute__((used)) static size_t rpc_out(void *ptr, size_t eltsize,
		size_t nmemb, void *buffer_)
{
	size_t max = eltsize * nmemb;
	struct rpc_state *rpc = buffer_;
	size_t avail = rpc->len - rpc->pos;
	enum packet_read_status status;

	if (!avail) {
		rpc->initial_buffer = 0;
		rpc->len = 0;
		rpc->pos = 0;
		if (!rpc->flush_read_but_not_sent) {
			if (!rpc_read_from_out(rpc, 0, &avail, &status))
				BUG("The entire rpc->buf should be larger than LARGE_PACKET_MAX");
			if (status == PACKET_READ_FLUSH)
				rpc->flush_read_but_not_sent = 1;
		}
		/*
		 * If flush_read_but_not_sent is true, we have already read one
		 * full request but have not fully sent it + EOF, which is why
		 * we need to refrain from reading.
		 */
	}
	if (rpc->flush_read_but_not_sent) {
		if (!avail) {
			/*
			 * The line length either does not need to be sent at
			 * all or has already been completely sent. Now we can
			 * return 0, indicating EOF, meaning that the flush has
			 * been fully sent.
			 */
			rpc->flush_read_but_not_sent = 0;
			return 0;
		}
		/*
		 * If avail is non-zerp, the line length for the flush still
		 * hasn't been fully sent. Proceed with sending the line
		 * length.
		 */
	}

	if (max < avail)
		avail = max;
	memcpy(ptr, rpc->buf + rpc->pos, avail);
	rpc->pos += avail;
	return avail;
}