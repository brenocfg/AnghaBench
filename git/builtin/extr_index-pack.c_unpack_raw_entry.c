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
struct object_id {int /*<<< orphan*/  hash; } ;
struct TYPE_3__ {int offset; int /*<<< orphan*/  crc32; } ;
struct object_entry {unsigned long type; unsigned long size; TYPE_1__ idx; void* hdr_size; } ;
typedef  int off_t ;
struct TYPE_4__ {int rawsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSB (int,int) ; 
#define  OBJ_BLOB 133 
#define  OBJ_COMMIT 132 
#define  OBJ_OFS_DELTA 131 
#define  OBJ_REF_DELTA 130 
#define  OBJ_TAG 129 
#define  OBJ_TREE 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  bad_object (int,int /*<<< orphan*/ ,...) ; 
 void* consumed_bytes ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned char* fill (int) ; 
 int /*<<< orphan*/  hashcpy (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  input_crc32 ; 
 TYPE_2__* the_hash_algo ; 
 void* unpack_entry_data (void*,unsigned long,long,struct object_id*) ; 
 int /*<<< orphan*/  use (int) ; 

__attribute__((used)) static void *unpack_raw_entry(struct object_entry *obj,
			      off_t *ofs_offset,
			      struct object_id *ref_oid,
			      struct object_id *oid)
{
	unsigned char *p;
	unsigned long size, c;
	off_t base_offset;
	unsigned shift;
	void *data;

	obj->idx.offset = consumed_bytes;
	input_crc32 = crc32(0, NULL, 0);

	p = fill(1);
	c = *p;
	use(1);
	obj->type = (c >> 4) & 7;
	size = (c & 15);
	shift = 4;
	while (c & 0x80) {
		p = fill(1);
		c = *p;
		use(1);
		size += (c & 0x7f) << shift;
		shift += 7;
	}
	obj->size = size;

	switch (obj->type) {
	case OBJ_REF_DELTA:
		hashcpy(ref_oid->hash, fill(the_hash_algo->rawsz));
		use(the_hash_algo->rawsz);
		break;
	case OBJ_OFS_DELTA:
		p = fill(1);
		c = *p;
		use(1);
		base_offset = c & 127;
		while (c & 128) {
			base_offset += 1;
			if (!base_offset || MSB(base_offset, 7))
				bad_object(obj->idx.offset, _("offset value overflow for delta base object"));
			p = fill(1);
			c = *p;
			use(1);
			base_offset = (base_offset << 7) + (c & 127);
		}
		*ofs_offset = obj->idx.offset - base_offset;
		if (*ofs_offset <= 0 || *ofs_offset >= obj->idx.offset)
			bad_object(obj->idx.offset, _("delta base offset is out of bound"));
		break;
	case OBJ_COMMIT:
	case OBJ_TREE:
	case OBJ_BLOB:
	case OBJ_TAG:
		break;
	default:
		bad_object(obj->idx.offset, _("unknown object type %d"), obj->type);
	}
	obj->hdr_size = consumed_bytes - obj->idx.offset;

	data = unpack_entry_data(obj->idx.offset, obj->size, obj->type, oid);
	obj->idx.crc32 = input_crc32;
	return data;
}