#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sshbuf {int dummy; } ;
struct ssh {TYPE_1__* state; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_4__ {int avail_out; int /*<<< orphan*/ * next_out; scalar_t__ avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_3__ {int compression_out_started; int /*<<< orphan*/  compression_out_failures; TYPE_2__ compression_out_stream; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
#define  Z_MEM_ERROR 130 
#define  Z_OK 129 
 int /*<<< orphan*/  Z_PARTIAL_FLUSH ; 
#define  Z_STREAM_ERROR 128 
 int deflate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/ * sshbuf_mutable_ptr (struct sshbuf*) ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
compress_buffer(struct ssh *ssh, struct sshbuf *in, struct sshbuf *out)
{
	u_char buf[4096];
	int r, status;

	if (ssh->state->compression_out_started != 1)
		return SSH_ERR_INTERNAL_ERROR;

	/* This case is not handled below. */
	if (sshbuf_len(in) == 0)
		return 0;

	/* Input is the contents of the input buffer. */
	if ((ssh->state->compression_out_stream.next_in =
	    sshbuf_mutable_ptr(in)) == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	ssh->state->compression_out_stream.avail_in = sshbuf_len(in);

	/* Loop compressing until deflate() returns with avail_out != 0. */
	do {
		/* Set up fixed-size output buffer. */
		ssh->state->compression_out_stream.next_out = buf;
		ssh->state->compression_out_stream.avail_out = sizeof(buf);

		/* Compress as much data into the buffer as possible. */
		status = deflate(&ssh->state->compression_out_stream,
		    Z_PARTIAL_FLUSH);
		switch (status) {
		case Z_MEM_ERROR:
			return SSH_ERR_ALLOC_FAIL;
		case Z_OK:
			/* Append compressed data to output_buffer. */
			if ((r = sshbuf_put(out, buf, sizeof(buf) -
			    ssh->state->compression_out_stream.avail_out)) != 0)
				return r;
			break;
		case Z_STREAM_ERROR:
		default:
			ssh->state->compression_out_failures++;
			return SSH_ERR_INVALID_FORMAT;
		}
	} while (ssh->state->compression_out_stream.avail_out == 0);
	return 0;
}