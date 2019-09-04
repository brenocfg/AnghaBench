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
typedef  scalar_t__ uint32_t ;
struct packed_git {scalar_t__* index_data; int num_objects; } ;
struct pack_window {int dummy; } ;
typedef  unsigned long off_t ;
struct TYPE_2__ {int rawsz; } ;

/* Variables and functions */
 scalar_t__ crc32 (scalar_t__,void*,unsigned long) ; 
 scalar_t__ ntohl (scalar_t__ const) ; 
 TYPE_1__* the_hash_algo ; 
 void* use_pack (struct packed_git*,struct pack_window**,unsigned long,unsigned long*) ; 

int check_pack_crc(struct packed_git *p, struct pack_window **w_curs,
		   off_t offset, off_t len, unsigned int nr)
{
	const uint32_t *index_crc;
	uint32_t data_crc = crc32(0, NULL, 0);

	do {
		unsigned long avail;
		void *data = use_pack(p, w_curs, offset, &avail);
		if (avail > len)
			avail = len;
		data_crc = crc32(data_crc, data, avail);
		offset += avail;
		len -= avail;
	} while (len);

	index_crc = p->index_data;
	index_crc += 2 + 256 + p->num_objects * (the_hash_algo->rawsz/4) + nr;

	return data_crc != ntohl(*index_crc);
}