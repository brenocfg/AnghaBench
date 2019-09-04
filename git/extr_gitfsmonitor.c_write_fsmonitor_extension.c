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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct strbuf {int len; scalar_t__ buf; } ;
struct index_state {int /*<<< orphan*/ * fsmonitor_dirty; int /*<<< orphan*/  fsmonitor_last_update; } ;

/* Variables and functions */
 int INDEX_EXTENSION_VERSION ; 
 int /*<<< orphan*/  ewah_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ewah_serialize_strbuf (int /*<<< orphan*/ *,struct strbuf*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int*,int) ; 
 int /*<<< orphan*/  put_be32 (int*,int) ; 
 int /*<<< orphan*/  put_be64 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_add (struct strbuf*,int*,int) ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*) ; 

void write_fsmonitor_extension(struct strbuf *sb, struct index_state *istate)
{
	uint32_t hdr_version;
	uint64_t tm;
	uint32_t ewah_start;
	uint32_t ewah_size = 0;
	int fixup = 0;

	put_be32(&hdr_version, INDEX_EXTENSION_VERSION);
	strbuf_add(sb, &hdr_version, sizeof(uint32_t));

	put_be64(&tm, istate->fsmonitor_last_update);
	strbuf_add(sb, &tm, sizeof(uint64_t));
	fixup = sb->len;
	strbuf_add(sb, &ewah_size, sizeof(uint32_t)); /* we'll fix this up later */

	ewah_start = sb->len;
	ewah_serialize_strbuf(istate->fsmonitor_dirty, sb);
	ewah_free(istate->fsmonitor_dirty);
	istate->fsmonitor_dirty = NULL;

	/* fix up size field */
	put_be32(&ewah_size, sb->len - ewah_start);
	memcpy(sb->buf + fixup, &ewah_size, sizeof(uint32_t));

	trace_printf_key(&trace_fsmonitor, "write fsmonitor extension successful");
}