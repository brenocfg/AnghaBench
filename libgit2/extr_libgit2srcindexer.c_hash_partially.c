#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {size_t inbuf_len; int /*<<< orphan*/  const* inbuf; int /*<<< orphan*/  trailer; } ;
typedef  TYPE_1__ git_indexer ;

/* Variables and functions */
 size_t GIT_OID_RAWSZ ; 
 int /*<<< orphan*/  git_hash_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static void hash_partially(git_indexer *idx, const uint8_t *data, size_t size)
{
	size_t to_expell, to_keep;

	if (size == 0)
		return;

	/* Easy case, dump the buffer and the data minus the last 20 bytes */
	if (size >= GIT_OID_RAWSZ) {
		git_hash_update(&idx->trailer, idx->inbuf, idx->inbuf_len);
		git_hash_update(&idx->trailer, data, size - GIT_OID_RAWSZ);

		data += size - GIT_OID_RAWSZ;
		memcpy(idx->inbuf, data, GIT_OID_RAWSZ);
		idx->inbuf_len = GIT_OID_RAWSZ;
		return;
	}

	/* We can just append */
	if (idx->inbuf_len + size <= GIT_OID_RAWSZ) {
		memcpy(idx->inbuf + idx->inbuf_len, data, size);
		idx->inbuf_len += size;
		return;
	}

	/* We need to partially drain the buffer and then append */
	to_keep   = GIT_OID_RAWSZ - size;
	to_expell = idx->inbuf_len - to_keep;

	git_hash_update(&idx->trailer, idx->inbuf, to_expell);

	memmove(idx->inbuf, idx->inbuf + to_expell, to_keep);
	memcpy(idx->inbuf + to_keep, data, size);
	idx->inbuf_len += size - to_expell;
}