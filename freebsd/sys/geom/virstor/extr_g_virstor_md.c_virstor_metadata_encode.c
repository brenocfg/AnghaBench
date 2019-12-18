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
struct g_virstor_metadata {int /*<<< orphan*/  flags; int /*<<< orphan*/  chunk_reserved; int /*<<< orphan*/  chunk_next; int /*<<< orphan*/  chunk_count; int /*<<< orphan*/  provsize; int /*<<< orphan*/  no; int /*<<< orphan*/  provider; int /*<<< orphan*/  md_count; int /*<<< orphan*/  md_id; int /*<<< orphan*/  md_chunk_size; int /*<<< orphan*/  md_virsize; int /*<<< orphan*/  md_name; int /*<<< orphan*/  md_version; int /*<<< orphan*/  md_magic; } ;
typedef  int /*<<< orphan*/  bin_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  bs_open (int /*<<< orphan*/ *,unsigned char*) ; 
 int /*<<< orphan*/  bs_write_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bs_write_u16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_write_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bs_write_u64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
virstor_metadata_encode(struct g_virstor_metadata *md, unsigned char *data)
{
	bin_stream_t bs;

	bs_open(&bs, data);

	bs_write_buf(&bs, md->md_magic, sizeof(md->md_magic));
	bs_write_u32(&bs, md->md_version);
	bs_write_buf(&bs, md->md_name, sizeof(md->md_name));
	bs_write_u64(&bs, md->md_virsize);
	bs_write_u32(&bs, md->md_chunk_size);
	bs_write_u32(&bs, md->md_id);
	bs_write_u16(&bs, md->md_count);

	bs_write_buf(&bs, md->provider, sizeof(md->provider));
	bs_write_u16(&bs, md->no);
	bs_write_u64(&bs, md->provsize);
	bs_write_u32(&bs, md->chunk_count);
	bs_write_u32(&bs, md->chunk_next);
	bs_write_u16(&bs, md->chunk_reserved);
	bs_write_u16(&bs, md->flags);
}