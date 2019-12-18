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
struct proxy_stream {int /*<<< orphan*/  temp_buf; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  git_writestream ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct proxy_stream*) ; 
 int /*<<< orphan*/  git__free (struct proxy_stream*) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void proxy_stream_free(git_writestream *s)
{
	struct proxy_stream *proxy_stream = (struct proxy_stream *)s;
	assert(proxy_stream);

	git_buf_dispose(&proxy_stream->input);
	git_buf_dispose(&proxy_stream->temp_buf);
	git__free(proxy_stream);
}