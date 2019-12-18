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
struct checkout_stream {int /*<<< orphan*/  fd; scalar_t__ open; } ;
typedef  int /*<<< orphan*/  git_writestream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int p_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_stream_close(git_writestream *s)
{
	struct checkout_stream *stream = (struct checkout_stream *)s;
	assert(stream && stream->open);

	stream->open = 0;
	return p_close(stream->fd);
}