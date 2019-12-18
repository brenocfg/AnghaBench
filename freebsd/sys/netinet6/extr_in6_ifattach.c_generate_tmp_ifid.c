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
typedef  int /*<<< orphan*/  val32 ;
typedef  int u_int8_t ;
typedef  int u_int32_t ;
typedef  int /*<<< orphan*/  seed ;
typedef  int /*<<< orphan*/  nullbuf ;
typedef  int /*<<< orphan*/  ctxt ;
typedef  int MD5_CTX ;

/* Variables and functions */
 int EUI64_UBIT ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  MD5Final (int*,int*) ; 
 int /*<<< orphan*/  MD5Init (int*) ; 
 int /*<<< orphan*/  MD5Update (int*,int*,int) ; 
 int arc4random () ; 
 scalar_t__ bcmp (int*,int*,int) ; 
 int /*<<< orphan*/  bcopy (int const*,int*,int) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  nd6log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int
generate_tmp_ifid(u_int8_t *seed0, const u_int8_t *seed1, u_int8_t *ret)
{
	MD5_CTX ctxt;
	u_int8_t seed[16], digest[16], nullbuf[8];
	u_int32_t val32;

	/* If there's no history, start with a random seed. */
	bzero(nullbuf, sizeof(nullbuf));
	if (bcmp(nullbuf, seed0, sizeof(nullbuf)) == 0) {
		int i;

		for (i = 0; i < 2; i++) {
			val32 = arc4random();
			bcopy(&val32, seed + sizeof(val32) * i, sizeof(val32));
		}
	} else
		bcopy(seed0, seed, 8);

	/* copy the right-most 64-bits of the given address */
	/* XXX assumption on the size of IFID */
	bcopy(seed1, &seed[8], 8);

	if (0) {		/* for debugging purposes only */
		int i;

		printf("generate_tmp_ifid: new randomized ID from: ");
		for (i = 0; i < 16; i++)
			printf("%02x", seed[i]);
		printf(" ");
	}

	/* generate 16 bytes of pseudo-random value. */
	bzero(&ctxt, sizeof(ctxt));
	MD5Init(&ctxt);
	MD5Update(&ctxt, seed, sizeof(seed));
	MD5Final(digest, &ctxt);

	/*
	 * RFC 3041 3.2.1. (3)
	 * Take the left-most 64-bits of the MD5 digest and set bit 6 (the
	 * left-most bit is numbered 0) to zero.
	 */
	bcopy(digest, ret, 8);
	ret[0] &= ~EUI64_UBIT;

	/*
	 * XXX: we'd like to ensure that the generated value is not zero
	 * for simplicity.  If the caclculated digest happens to be zero,
	 * use a random non-zero value as the last resort.
	 */
	if (bcmp(nullbuf, ret, sizeof(nullbuf)) == 0) {
		nd6log((LOG_INFO,
		    "generate_tmp_ifid: computed MD5 value is zero.\n"));

		val32 = arc4random();
		val32 = 1 + (val32 % (0xffffffff - 1));
	}

	/*
	 * RFC 3041 3.2.1. (4)
	 * Take the rightmost 64-bits of the MD5 digest and save them in
	 * stable storage as the history value to be used in the next
	 * iteration of the algorithm.
	 */
	bcopy(&digest[8], seed0, 8);

	if (0) {		/* for debugging purposes only */
		int i;

		printf("to: ");
		for (i = 0; i < 16; i++)
			printf("%02x", digest[i]);
		printf("\n");
	}

	return 0;
}