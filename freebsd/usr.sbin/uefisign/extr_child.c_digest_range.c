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
struct executable {scalar_t__ x_buf; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  EVP_MD_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_print_errors_fp (int /*<<< orphan*/ ) ; 
 int EVP_DigestUpdate (int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  range_check (struct executable*,scalar_t__,size_t,char*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
digest_range(struct executable *x, EVP_MD_CTX *mdctx, off_t off, size_t len)
{
	int ok;

	range_check(x, off, len, "chunk");

	ok = EVP_DigestUpdate(mdctx, x->x_buf + off, len);
	if (ok == 0) {
		ERR_print_errors_fp(stderr);
		errx(1, "EVP_DigestUpdate(3) failed");
	}
}