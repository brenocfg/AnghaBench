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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  SHA1_CTX ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  CHOMP (unsigned char*,int,int) ; 
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  SHA1Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHA1Update (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hexdump (unsigned char*,int) ; 
 scalar_t__ mflag ; 
 int /*<<< orphan*/  stdin ; 
 int strlen (char*) ; 

__attribute__((used)) static void
regress(void)
{
	unsigned char buf[1024];
	unsigned char out[20];
	int len, outlen, last;
	
	while (fgets((char *)buf, sizeof(buf), stdin) != NULL) {
		last = 0;

		len = strlen((char *)buf);
		CHOMP(buf, len, last);
		if (mflag) {
			MD5_CTX ctx;

			MD5Init(&ctx);
			MD5Update(&ctx, buf, len);
			while (!last &&
			    fgets((char *)buf, sizeof(buf), stdin) != NULL) {
				len = strlen((char *)buf);
				CHOMP(buf, len, last);
				MD5Update(&ctx, buf, len);
			}
			MD5Final(out, &ctx);
			outlen = 16;
		} else {
			SHA1_CTX ctx;

			SHA1Init(&ctx);
			SHA1Update(&ctx, buf, len);
			while (!last &&
			    fgets((char *)buf, sizeof(buf), stdin) != NULL) {
				len = strlen((char *)buf);
				CHOMP(buf, len, last);				
				SHA1Update(&ctx, buf, len);
			}
			SHA1Final(out, &ctx);
			outlen = 20;
		}
		hexdump(out, outlen);
	}
}