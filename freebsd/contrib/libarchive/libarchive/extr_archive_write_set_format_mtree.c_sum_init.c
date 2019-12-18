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
struct mtree_writer {int compute_sum; int keys; int /*<<< orphan*/  sha512ctx; int /*<<< orphan*/  sha384ctx; int /*<<< orphan*/  sha256ctx; int /*<<< orphan*/  sha1ctx; int /*<<< orphan*/  rmd160ctx; int /*<<< orphan*/  md5ctx; scalar_t__ crc_len; scalar_t__ crc; } ;

/* Variables and functions */
 scalar_t__ ARCHIVE_OK ; 
 int F_CKSUM ; 
 int F_MD5 ; 
 int F_RMD160 ; 
 int F_SHA1 ; 
 int F_SHA256 ; 
 int F_SHA384 ; 
 int F_SHA512 ; 
 scalar_t__ archive_md5_init (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_rmd160_init (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_sha1_init (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_sha256_init (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_sha384_init (int /*<<< orphan*/ *) ; 
 scalar_t__ archive_sha512_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sum_init(struct mtree_writer *mtree)
{

	mtree->compute_sum = 0;

	if (mtree->keys & F_CKSUM) {
		mtree->compute_sum |= F_CKSUM;
		mtree->crc = 0;
		mtree->crc_len = 0;
	}
#ifdef ARCHIVE_HAS_MD5
	if (mtree->keys & F_MD5) {
		if (archive_md5_init(&mtree->md5ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_MD5;
		else
			mtree->keys &= ~F_MD5;/* Not supported. */
	}
#endif
#ifdef ARCHIVE_HAS_RMD160
	if (mtree->keys & F_RMD160) {
		if (archive_rmd160_init(&mtree->rmd160ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_RMD160;
		else
			mtree->keys &= ~F_RMD160;/* Not supported. */
	}
#endif
#ifdef ARCHIVE_HAS_SHA1
	if (mtree->keys & F_SHA1) {
		if (archive_sha1_init(&mtree->sha1ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA1;
		else
			mtree->keys &= ~F_SHA1;/* Not supported. */
	}
#endif
#ifdef ARCHIVE_HAS_SHA256
	if (mtree->keys & F_SHA256) {
		if (archive_sha256_init(&mtree->sha256ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA256;
		else
			mtree->keys &= ~F_SHA256;/* Not supported. */
	}
#endif
#ifdef ARCHIVE_HAS_SHA384
	if (mtree->keys & F_SHA384) {
		if (archive_sha384_init(&mtree->sha384ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA384;
		else
			mtree->keys &= ~F_SHA384;/* Not supported. */
	}
#endif
#ifdef ARCHIVE_HAS_SHA512
	if (mtree->keys & F_SHA512) {
		if (archive_sha512_init(&mtree->sha512ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA512;
		else
			mtree->keys &= ~F_SHA512;/* Not supported. */
	}
#endif
}