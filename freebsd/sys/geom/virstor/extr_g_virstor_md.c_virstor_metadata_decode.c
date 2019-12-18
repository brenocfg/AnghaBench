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
struct g_virstor_metadata {void* flags; void* chunk_reserved; void* chunk_next; void* chunk_count; void* provsize; void* no; int /*<<< orphan*/  provider; void* md_count; void* md_id; void* md_chunk_size; void* md_virsize; int /*<<< orphan*/  md_name; void* md_version; int /*<<< orphan*/  md_magic; } ;
typedef  int /*<<< orphan*/  bin_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_open (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bs_read_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* bs_read_u16 (int /*<<< orphan*/ *) ; 
 void* bs_read_u32 (int /*<<< orphan*/ *) ; 
 void* bs_read_u64 (int /*<<< orphan*/ *) ; 

void
virstor_metadata_decode(unsigned char *data, struct g_virstor_metadata *md)
{
	bin_stream_t bs;

	bs_open(&bs, (char *)(data));

	bs_read_buf(&bs, md->md_magic, sizeof(md->md_magic));
	md->md_version = bs_read_u32(&bs);
	bs_read_buf(&bs, md->md_name, sizeof(md->md_name));
	md->md_virsize = bs_read_u64(&bs);
	md->md_chunk_size = bs_read_u32(&bs);
	md->md_id = bs_read_u32(&bs);
	md->md_count = bs_read_u16(&bs);

	bs_read_buf(&bs, md->provider, sizeof(md->provider));
	md->no = bs_read_u16(&bs);
	md->provsize = bs_read_u64(&bs);
	md->chunk_count = bs_read_u32(&bs);
	md->chunk_next = bs_read_u32(&bs);
	md->chunk_reserved = bs_read_u16(&bs);
	md->flags = bs_read_u16(&bs);
}