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
struct mtree_writer {int compute_sum; size_t crc_len; int /*<<< orphan*/  sha512ctx; int /*<<< orphan*/  sha384ctx; int /*<<< orphan*/  sha256ctx; int /*<<< orphan*/  sha1ctx; int /*<<< orphan*/  rmd160ctx; int /*<<< orphan*/  md5ctx; int /*<<< orphan*/  crc; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPUTE_CRC (int /*<<< orphan*/ ,unsigned char const) ; 
 int F_CKSUM ; 
 int F_MD5 ; 
 int F_RMD160 ; 
 int F_SHA1 ; 
 int F_SHA256 ; 
 int F_SHA384 ; 
 int F_SHA512 ; 
 int /*<<< orphan*/  archive_md5_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  archive_rmd160_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  archive_sha1_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  archive_sha256_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  archive_sha384_update (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  archive_sha512_update (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static void
sum_update(struct mtree_writer *mtree, const void *buff, size_t n)
{
	if (mtree->compute_sum & F_CKSUM) {
		/*
		 * Compute a POSIX 1003.2 checksum
		 */
		const unsigned char *p;
		size_t nn;

		for (nn = n, p = buff; nn--; ++p)
			COMPUTE_CRC(mtree->crc, *p);
		mtree->crc_len += n;
	}
#ifdef ARCHIVE_HAS_MD5
	if (mtree->compute_sum & F_MD5)
		archive_md5_update(&mtree->md5ctx, buff, n);
#endif
#ifdef ARCHIVE_HAS_RMD160
	if (mtree->compute_sum & F_RMD160)
		archive_rmd160_update(&mtree->rmd160ctx, buff, n);
#endif
#ifdef ARCHIVE_HAS_SHA1
	if (mtree->compute_sum & F_SHA1)
		archive_sha1_update(&mtree->sha1ctx, buff, n);
#endif
#ifdef ARCHIVE_HAS_SHA256
	if (mtree->compute_sum & F_SHA256)
		archive_sha256_update(&mtree->sha256ctx, buff, n);
#endif
#ifdef ARCHIVE_HAS_SHA384
	if (mtree->compute_sum & F_SHA384)
		archive_sha384_update(&mtree->sha384ctx, buff, n);
#endif
#ifdef ARCHIVE_HAS_SHA512
	if (mtree->compute_sum & F_SHA512)
		archive_sha512_update(&mtree->sha512ctx, buff, n);
#endif
}