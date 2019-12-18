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
struct executable {size_t x_checksum_off; size_t x_checksum_len; size_t x_certificate_entry_off; size_t x_certificate_entry_len; size_t x_headers_len; int x_nsections; size_t* x_section_off; size_t* x_section_len; size_t x_len; int /*<<< orphan*/  x_digest_len; int /*<<< orphan*/  x_digest; } ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;
typedef  int /*<<< orphan*/  EVP_MD ;

/* Variables and functions */
 int /*<<< orphan*/  DIGEST ; 
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int EVP_DigestFinal_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int EVP_DigestInit_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_MD_CTX_create () ; 
 int /*<<< orphan*/  EVP_MD_CTX_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EVP_get_digestbyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digest_range (struct executable*,int /*<<< orphan*/ *,size_t,size_t) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 size_t signature_size (struct executable*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
digest(struct executable *x)
{
	EVP_MD_CTX *mdctx;
	const EVP_MD *md;
	size_t sum_of_bytes_hashed;
	int i, ok;

	/*
	 * Windows Authenticode Portable Executable Signature Format
	 * spec version 1.0 specifies MD5 and SHA1.  However, pesign
	 * and sbsign both use SHA256, so do the same.
	 */
	md = EVP_get_digestbyname(DIGEST);
	if (md == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_get_digestbyname(\"%s\") failed", DIGEST);
	}

	mdctx = EVP_MD_CTX_create();
	if (mdctx == NULL) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_MD_CTX_create(3) failed");
	}

	ok = EVP_DigestInit_ex(mdctx, md, NULL);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_DigestInit_ex(3) failed");
	}

	/*
	 * According to the Authenticode spec, we need to compute
	 * the digest in a rather... specific manner; see "Calculating
	 * the PE Image Hash" part of the spec for details.
	 *
	 * First, everything from 0 to before the PE checksum.
	 */
	digest_range(x, mdctx, 0, x->x_checksum_off);

	/*
	 * Second, from after the PE checksum to before the Certificate
	 * entry in Data Directory.
	 */
	digest_range(x, mdctx, x->x_checksum_off + x->x_checksum_len,
	    x->x_certificate_entry_off -
	    (x->x_checksum_off + x->x_checksum_len));

	/*
	 * Then, from after the Certificate entry to the end of headers.
	 */
	digest_range(x, mdctx,
	    x->x_certificate_entry_off + x->x_certificate_entry_len,
	    x->x_headers_len -
	    (x->x_certificate_entry_off + x->x_certificate_entry_len));

	/*
	 * Then, each section in turn, as specified in the PE Section Table.
	 *
	 * XXX: Sorting.
	 */
	sum_of_bytes_hashed = x->x_headers_len;
	for (i = 0; i < x->x_nsections; i++) {
		digest_range(x, mdctx,
		    x->x_section_off[i], x->x_section_len[i]);
		sum_of_bytes_hashed += x->x_section_len[i];
	}

	/*
	 * I believe this can happen with overlapping sections.
	 */
	if (sum_of_bytes_hashed > x->x_len)
		errx(1, "number of bytes hashed is larger than file size");

	/*
	 * I can't really explain this one; just do what the spec says.
	 */
	if (sum_of_bytes_hashed < x->x_len) {
		digest_range(x, mdctx, sum_of_bytes_hashed,
		    x->x_len - (signature_size(x) + sum_of_bytes_hashed));
	}

	ok = EVP_DigestFinal_ex(mdctx, x->x_digest, &x->x_digest_len);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_DigestFinal_ex(3) failed");
	}

	EVP_MD_CTX_destroy(mdctx);
}