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
typedef  int /*<<< orphan*/  u_long ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ OPENSSL_VERSION_NUMBER ; 
 int RANDOM_SEED_SIZE ; 
 int /*<<< orphan*/  RAND_add (unsigned char*,int,int) ; 
 int RAND_status () ; 
 int /*<<< orphan*/  SSLeay () ; 
 int /*<<< orphan*/  debug3 (char*) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  memset (unsigned char*,char,int) ; 
 int seed_from_prngd (unsigned char*,int) ; 
 int /*<<< orphan*/  ssh_compatible_openssl (scalar_t__,int /*<<< orphan*/ ) ; 

void
seed_rng(void)
{
#ifndef OPENSSL_PRNG_ONLY
	unsigned char buf[RANDOM_SEED_SIZE];
#endif
	if (!ssh_compatible_openssl(OPENSSL_VERSION_NUMBER, SSLeay()))
		fatal("OpenSSL version mismatch. Built against %lx, you "
		    "have %lx", (u_long)OPENSSL_VERSION_NUMBER, SSLeay());

#ifndef OPENSSL_PRNG_ONLY
	if (RAND_status() == 1) {
		debug3("RNG is ready, skipping seeding");
		return;
	}

	if (seed_from_prngd(buf, sizeof(buf)) == -1)
		fatal("Could not obtain seed from PRNGd");
	RAND_add(buf, sizeof(buf), sizeof(buf));
	memset(buf, '\0', sizeof(buf));

#endif /* OPENSSL_PRNG_ONLY */
	if (RAND_status() != 1)
		fatal("PRNG is not seeded");
}