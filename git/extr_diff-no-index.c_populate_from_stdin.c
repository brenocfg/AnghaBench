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
struct strbuf {int dummy; } ;
struct diff_filespec {size_t size; int should_free; int is_stdin; int /*<<< orphan*/  data; scalar_t__ should_munmap; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int error_errno (char*) ; 
 int /*<<< orphan*/  strbuf_detach (struct strbuf*,size_t*) ; 
 scalar_t__ strbuf_read (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int populate_from_stdin(struct diff_filespec *s)
{
	struct strbuf buf = STRBUF_INIT;
	size_t size = 0;

	if (strbuf_read(&buf, 0, 0) < 0)
		return error_errno("error while reading from stdin");

	s->should_munmap = 0;
	s->data = strbuf_detach(&buf, &size);
	s->size = size;
	s->should_free = 1;
	s->is_stdin = 1;
	return 0;
}