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
struct reg_info {int compute_sum; int /*<<< orphan*/  buf_sha512; int /*<<< orphan*/  buf_sha384; int /*<<< orphan*/  buf_sha256; int /*<<< orphan*/  buf_sha1; int /*<<< orphan*/  buf_rmd160; int /*<<< orphan*/  buf_md5; int /*<<< orphan*/  crc; } ;
struct mtree_writer {int compute_sum; int crc_len; int /*<<< orphan*/  sha512ctx; int /*<<< orphan*/  sha384ctx; int /*<<< orphan*/  sha256ctx; int /*<<< orphan*/  sha1ctx; int /*<<< orphan*/  rmd160ctx; int /*<<< orphan*/  md5ctx; int /*<<< orphan*/  crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_CRC (int /*<<< orphan*/ ,int) ; 
 int F_CKSUM ; 
 int F_MD5 ; 
 int F_RMD160 ; 
 int F_SHA1 ; 
 int F_SHA256 ; 
 int F_SHA384 ; 
 int F_SHA512 ; 
 int /*<<< orphan*/  archive_md5_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_rmd160_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_sha1_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_sha256_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_sha384_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_sha512_final (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sum_final(struct mtree_writer *mtree, struct reg_info *reg)
{

	if (mtree->compute_sum & F_CKSUM) {
		uint64_t len;
		/* Include the length of the file. */
		for (len = mtree->crc_len; len != 0; len >>= 8)
			COMPUTE_CRC(mtree->crc, len & 0xff);
		reg->crc = ~mtree->crc;
	}
#ifdef ARCHIVE_HAS_MD5
	if (mtree->compute_sum & F_MD5)
		archive_md5_final(&mtree->md5ctx, reg->buf_md5);
#endif
#ifdef ARCHIVE_HAS_RMD160
	if (mtree->compute_sum & F_RMD160)
		archive_rmd160_final(&mtree->rmd160ctx, reg->buf_rmd160);
#endif
#ifdef ARCHIVE_HAS_SHA1
	if (mtree->compute_sum & F_SHA1)
		archive_sha1_final(&mtree->sha1ctx, reg->buf_sha1);
#endif
#ifdef ARCHIVE_HAS_SHA256
	if (mtree->compute_sum & F_SHA256)
		archive_sha256_final(&mtree->sha256ctx, reg->buf_sha256);
#endif
#ifdef ARCHIVE_HAS_SHA384
	if (mtree->compute_sum & F_SHA384)
		archive_sha384_final(&mtree->sha384ctx, reg->buf_sha384);
#endif
#ifdef ARCHIVE_HAS_SHA512
	if (mtree->compute_sum & F_SHA512)
		archive_sha512_final(&mtree->sha512ctx, reg->buf_sha512);
#endif
	/* Save what types of sum are computed. */
	reg->compute_sum = mtree->compute_sum;
}