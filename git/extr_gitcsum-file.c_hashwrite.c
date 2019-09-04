#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct hashfile {unsigned int offset; void* buffer; int /*<<< orphan*/  ctx; int /*<<< orphan*/  crc32; scalar_t__ do_crc; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* update_fn ) (int /*<<< orphan*/ *,void const*,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,void const*,unsigned int) ; 
 int /*<<< orphan*/  flush (struct hashfile*,void const*,unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,void const*,unsigned int) ; 
 TYPE_1__* the_hash_algo ; 

void hashwrite(struct hashfile *f, const void *buf, unsigned int count)
{
	while (count) {
		unsigned offset = f->offset;
		unsigned left = sizeof(f->buffer) - offset;
		unsigned nr = count > left ? left : count;
		const void *data;

		if (f->do_crc)
			f->crc32 = crc32(f->crc32, buf, nr);

		if (nr == sizeof(f->buffer)) {
			/* process full buffer directly without copy */
			data = buf;
		} else {
			memcpy(f->buffer + offset, buf, nr);
			data = f->buffer;
		}

		count -= nr;
		offset += nr;
		buf = (char *) buf + nr;
		left -= nr;
		if (!left) {
			the_hash_algo->update_fn(&f->ctx, data, offset);
			flush(f, data, offset);
			offset = 0;
		}
		f->offset = offset;
	}
}