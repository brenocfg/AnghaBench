#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  hash; } ;
struct TYPE_4__ {TYPE_1__ oid; int /*<<< orphan*/  crc32; scalar_t__ offset; } ;
struct object_entry {unsigned long size; int hdr_size; int type; int real_type; TYPE_2__ idx; } ;
struct hashfile {int dummy; } ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;

/* Variables and functions */
 int /*<<< orphan*/  crc32_begin (struct hashfile*) ; 
 int /*<<< orphan*/  crc32_end (struct hashfile*) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char const*) ; 
 int /*<<< orphan*/  hashflush (struct hashfile*) ; 
 int /*<<< orphan*/  hashwrite (struct hashfile*,unsigned char*,int) ; 
 int /*<<< orphan*/  nr_objects ; 
 struct object_entry* objects ; 
 scalar_t__ write_compressed (struct hashfile*,void*,unsigned long) ; 

__attribute__((used)) static struct object_entry *append_obj_to_pack(struct hashfile *f,
			       const unsigned char *sha1, void *buf,
			       unsigned long size, enum object_type type)
{
	struct object_entry *obj = &objects[nr_objects++];
	unsigned char header[10];
	unsigned long s = size;
	int n = 0;
	unsigned char c = (type << 4) | (s & 15);
	s >>= 4;
	while (s) {
		header[n++] = c | 0x80;
		c = s & 0x7f;
		s >>= 7;
	}
	header[n++] = c;
	crc32_begin(f);
	hashwrite(f, header, n);
	obj[0].size = size;
	obj[0].hdr_size = n;
	obj[0].type = type;
	obj[0].real_type = type;
	obj[1].idx.offset = obj[0].idx.offset + n;
	obj[1].idx.offset += write_compressed(f, buf, size);
	obj[0].idx.crc32 = crc32_end(f);
	hashflush(f);
	hashcpy(obj->idx.oid.hash, sha1);
	return obj;
}