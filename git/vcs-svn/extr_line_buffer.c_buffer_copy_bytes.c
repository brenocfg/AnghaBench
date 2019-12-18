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
struct line_buffer {int /*<<< orphan*/  infile; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int COPY_BUFFER_LEN ; 
 scalar_t__ buffer_skip_bytes (struct line_buffer*,scalar_t__) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (char*,int,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

off_t buffer_copy_bytes(struct line_buffer *buf, off_t nbytes)
{
	char byte_buffer[COPY_BUFFER_LEN];
	off_t done = 0;
	while (done < nbytes && !feof(buf->infile) && !ferror(buf->infile)) {
		off_t len = nbytes - done;
		size_t in = len < COPY_BUFFER_LEN ? len : COPY_BUFFER_LEN;
		in = fread(byte_buffer, 1, in, buf->infile);
		done += in;
		fwrite(byte_buffer, 1, in, stdout);
		if (ferror(stdout))
			return done + buffer_skip_bytes(buf, nbytes - done);
	}
	return done;
}