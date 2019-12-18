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
struct index_entry {unsigned char* ptr; unsigned int val; struct index_entry* next; } ;
struct git_delta_index {size_t src_size; unsigned char* src_buf; unsigned int hash_mask; struct index_entry** hash; } ;

/* Variables and functions */
 int GIT_EBUFS ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (unsigned char*) ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  GIT_ERROR_NOMEMORY ; 
 size_t MAX_OP_SIZE ; 
 unsigned int RABIN_SHIFT ; 
 unsigned int RABIN_WINDOW ; 
 unsigned int* T ; 
 unsigned int* U ; 
 size_t UINT_MAX ; 
 int /*<<< orphan*/  git__free (unsigned char*) ; 
 unsigned char* git__malloc (unsigned int) ; 
 unsigned char* git__realloc (unsigned char*,unsigned int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_delta_create_from_index(
	void **out,
	size_t *out_len,
	const struct git_delta_index *index,
	const void *trg_buf,
	size_t trg_size,
	size_t max_size)
{
	unsigned int i, bufpos, bufsize, moff, msize, val;
	int inscnt;
	const unsigned char *ref_data, *ref_top, *data, *top;
	unsigned char *buf;

	*out = NULL;
	*out_len = 0;

	if (!trg_buf || !trg_size)
		return 0;

	if (index->src_size > UINT_MAX ||
	    trg_size > UINT_MAX ||
	    max_size > (UINT_MAX - MAX_OP_SIZE - 1)) {
		git_error_set(GIT_ERROR_INVALID, "buffer sizes too large for delta processing");
		return -1;
	}

	bufpos = 0;
	bufsize = 8192;
	if (max_size && bufsize >= max_size)
		bufsize = (unsigned int)(max_size + MAX_OP_SIZE + 1);
	buf = git__malloc(bufsize);
	GIT_ERROR_CHECK_ALLOC(buf);

	/* store reference buffer size */
	i = (unsigned int)index->src_size;
	while (i >= 0x80) {
		buf[bufpos++] = i | 0x80;
		i >>= 7;
	}
	buf[bufpos++] = i;

	/* store target buffer size */
	i = (unsigned int)trg_size;
	while (i >= 0x80) {
		buf[bufpos++] = i | 0x80;
		i >>= 7;
	}
	buf[bufpos++] = i;

	ref_data = index->src_buf;
	ref_top = ref_data + index->src_size;
	data = trg_buf;
	top = (const unsigned char *) trg_buf + trg_size;

	bufpos++;
	val = 0;
	for (i = 0; i < RABIN_WINDOW && data < top; i++, data++) {
		buf[bufpos++] = *data;
		val = ((val << 8) | *data) ^ T[val >> RABIN_SHIFT];
	}
	inscnt = i;

	moff = 0;
	msize = 0;
	while (data < top) {
		if (msize < 4096) {
			struct index_entry *entry;
			val ^= U[data[-RABIN_WINDOW]];
			val = ((val << 8) | *data) ^ T[val >> RABIN_SHIFT];
			i = val & index->hash_mask;
			for (entry = index->hash[i]; entry; entry = entry->next) {
				const unsigned char *ref = entry->ptr;
				const unsigned char *src = data;
				unsigned int ref_size = (unsigned int)(ref_top - ref);
				if (entry->val != val)
					continue;
				if (ref_size > (unsigned int)(top - src))
					ref_size = (unsigned int)(top - src);
				if (ref_size <= msize)
					break;
				while (ref_size-- && *src++ == *ref)
					ref++;
				if (msize < (unsigned int)(ref - entry->ptr)) {
					/* this is our best match so far */
					msize = (unsigned int)(ref - entry->ptr);
					moff = (unsigned int)(entry->ptr - ref_data);
					if (msize >= 4096) /* good enough */
						break;
				}
			}
		}

		if (msize < 4) {
			if (!inscnt)
				bufpos++;
			buf[bufpos++] = *data++;
			inscnt++;
			if (inscnt == 0x7f) {
				buf[bufpos - inscnt - 1] = inscnt;
				inscnt = 0;
			}
			msize = 0;
		} else {
			unsigned int left;
			unsigned char *op;

			if (inscnt) {
				while (moff && ref_data[moff-1] == data[-1]) {
					/* we can match one byte back */
					msize++;
					moff--;
					data--;
					bufpos--;
					if (--inscnt)
						continue;
					bufpos--;  /* remove count slot */
					inscnt--;  /* make it -1 */
					break;
				}
				buf[bufpos - inscnt - 1] = inscnt;
				inscnt = 0;
			}

			/* A copy op is currently limited to 64KB (pack v2) */
			left = (msize < 0x10000) ? 0 : (msize - 0x10000);
			msize -= left;

			op = buf + bufpos++;
			i = 0x80;

			if (moff & 0x000000ff)
				buf[bufpos++] = moff >> 0,  i |= 0x01;
			if (moff & 0x0000ff00)
				buf[bufpos++] = moff >> 8,  i |= 0x02;
			if (moff & 0x00ff0000)
				buf[bufpos++] = moff >> 16, i |= 0x04;
			if (moff & 0xff000000)
				buf[bufpos++] = moff >> 24, i |= 0x08;

			if (msize & 0x00ff)
				buf[bufpos++] = msize >> 0, i |= 0x10;
			if (msize & 0xff00)
				buf[bufpos++] = msize >> 8, i |= 0x20;

			*op = i;

			data += msize;
			moff += msize;
			msize = left;

			if (msize < 4096) {
				int j;
				val = 0;
				for (j = -RABIN_WINDOW; j < 0; j++)
					val = ((val << 8) | data[j])
					      ^ T[val >> RABIN_SHIFT];
			}
		}

		if (bufpos >= bufsize - MAX_OP_SIZE) {
			void *tmp = buf;
			bufsize = bufsize * 3 / 2;
			if (max_size && bufsize >= max_size)
				bufsize = (unsigned int)(max_size + MAX_OP_SIZE + 1);
			if (max_size && bufpos > max_size)
				break;
			buf = git__realloc(buf, bufsize);
			if (!buf) {
				git__free(tmp);
				return -1;
			}
		}
	}

	if (inscnt)
		buf[bufpos - inscnt - 1] = inscnt;

	if (max_size && bufpos > max_size) {
		git_error_set(GIT_ERROR_NOMEMORY, "delta would be larger than maximum size");
		git__free(buf);
		return GIT_EBUFS;
	}

	*out_len = bufpos;
	*out = buf;
	return 0;
}