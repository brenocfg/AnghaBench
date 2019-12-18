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
struct TYPE_4__ {int avail_out; int /*<<< orphan*/ * next_out; int /*<<< orphan*/  avail_in; int /*<<< orphan*/ * next_in; } ;
struct TYPE_3__ {int compression_in_started; int /*<<< orphan*/  compression_in_failures; TYPE_2__ compression_in_stream; } ;

/* Variables and functions */
 int SSH_ERR_ALLOC_FAIL ; 
 int SSH_ERR_INTERNAL_ERROR ; 
 int SSH_ERR_INVALID_FORMAT ; 
#define  Z_BUF_ERROR 132 
#define  Z_DATA_ERROR 131 
#define  Z_MEM_ERROR 130 
#define  Z_OK 129 
 int /*<<< orphan*/  Z_PARTIAL_FLUSH ; 
#define  Z_STREAM_ERROR 128 
 int inflate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sshbuf_len (struct sshbuf*) ; 
 int /*<<< orphan*/ * sshbuf_mutable_ptr (struct sshbuf*) ; 
 int sshbuf_put (struct sshbuf*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
uncompress_buffer(struct ssh *ssh, struct sshbuf *in, struct sshbuf *out)
{
	u_char buf[4096];
	int r, status;

	if (ssh->state->compression_in_started != 1)
		return SSH_ERR_INTERNAL_ERROR;

	if ((ssh->state->compression_in_stream.next_in =
	    sshbuf_mutable_ptr(in)) == NULL)
		return SSH_ERR_INTERNAL_ERROR;
	ssh->state->compression_in_stream.avail_in = sshbuf_len(in);

	for (;;) {
		/* Set up fixed-size output buffer. */
		ssh->state->compression_in_stream.next_out = buf;
		ssh->state->compression_in_stream.avail_out = sizeof(buf);

		status = inflate(&ssh->state->compression_in_stream,
		    Z_PARTIAL_FLUSH);
		switch (status) {
		case Z_OK:
			if ((r = sshbuf_put(out, buf, sizeof(buf) -
			    ssh->state->compression_in_stream.avail_out)) != 0)
				return r;
			break;
		case Z_BUF_ERROR:
			/*
			 * Comments in zlib.h say that we should keep calling
			 * inflate() until we get an error.  This appears to
			 * be the error that we get.
			 */
			return 0;
		case Z_DATA_ERROR:
			return SSH_ERR_INVALID_FORMAT;
		case Z_MEM_ERROR:
			return SSH_ERR_ALLOC_FAIL;
		case Z_STREAM_ERROR:
		default:
			ssh->state->compression_in_failures++;
			return SSH_ERR_INTERNAL_ERROR;
		}
	}
	/* NOTREACHED */
}