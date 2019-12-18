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
struct strbuf {int /*<<< orphan*/  buf; } ;
struct line_buffer {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  magic ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int error (char*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ read_chunk (struct line_buffer*,int /*<<< orphan*/ *,struct strbuf*,int) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int read_magic(struct line_buffer *in, off_t *len)
{
	static const char magic[] = {'S', 'V', 'N', '\0'};
	struct strbuf sb = STRBUF_INIT;

	if (read_chunk(in, len, &sb, sizeof(magic))) {
		strbuf_release(&sb);
		return -1;
	}
	if (memcmp(sb.buf, magic, sizeof(magic))) {
		strbuf_release(&sb);
		return error("invalid delta: unrecognized file type");
	}
	strbuf_release(&sb);
	return 0;
}