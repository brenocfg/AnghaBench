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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint32_t ;
struct index_state {struct ewah_bitmap* fsmonitor_dirty; int /*<<< orphan*/  fsmonitor_last_update; } ;
struct ewah_bitmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ INDEX_EXTENSION_VERSION ; 
 int error (char*,...) ; 
 int /*<<< orphan*/  ewah_free (struct ewah_bitmap*) ; 
 struct ewah_bitmap* ewah_new () ; 
 int ewah_read_mmap (struct ewah_bitmap*,char const*,scalar_t__) ; 
 scalar_t__ get_be32 (char const*) ; 
 int /*<<< orphan*/  get_be64 (char const*) ; 
 int /*<<< orphan*/  trace_fsmonitor ; 
 int /*<<< orphan*/  trace_printf_key (int /*<<< orphan*/ *,char*) ; 

int read_fsmonitor_extension(struct index_state *istate, const void *data,
	unsigned long sz)
{
	const char *index = data;
	uint32_t hdr_version;
	uint32_t ewah_size;
	struct ewah_bitmap *fsmonitor_dirty;
	int ret;

	if (sz < sizeof(uint32_t) + sizeof(uint64_t) + sizeof(uint32_t))
		return error("corrupt fsmonitor extension (too short)");

	hdr_version = get_be32(index);
	index += sizeof(uint32_t);
	if (hdr_version != INDEX_EXTENSION_VERSION)
		return error("bad fsmonitor version %d", hdr_version);

	istate->fsmonitor_last_update = get_be64(index);
	index += sizeof(uint64_t);

	ewah_size = get_be32(index);
	index += sizeof(uint32_t);

	fsmonitor_dirty = ewah_new();
	ret = ewah_read_mmap(fsmonitor_dirty, index, ewah_size);
	if (ret != ewah_size) {
		ewah_free(fsmonitor_dirty);
		return error("failed to parse ewah bitmap reading fsmonitor index extension");
	}
	istate->fsmonitor_dirty = fsmonitor_dirty;

	trace_printf_key(&trace_fsmonitor, "read fsmonitor extension successful");
	return 0;
}