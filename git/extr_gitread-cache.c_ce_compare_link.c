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
struct strbuf {unsigned long len; int /*<<< orphan*/  buf; } ;
struct cache_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  name; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  free (void*) ; 
 int memcmp (void*,int /*<<< orphan*/ ,unsigned long) ; 
 void* read_object_file (int /*<<< orphan*/ *,int*,unsigned long*) ; 
 scalar_t__ strbuf_readlink (struct strbuf*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int ce_compare_link(const struct cache_entry *ce, size_t expected_size)
{
	int match = -1;
	void *buffer;
	unsigned long size;
	enum object_type type;
	struct strbuf sb = STRBUF_INIT;

	if (strbuf_readlink(&sb, ce->name, expected_size))
		return -1;

	buffer = read_object_file(&ce->oid, &type, &size);
	if (buffer) {
		if (size == sb.len)
			match = memcmp(buffer, sb.buf, size);
		free(buffer);
	}
	strbuf_release(&sb);
	return match;
}