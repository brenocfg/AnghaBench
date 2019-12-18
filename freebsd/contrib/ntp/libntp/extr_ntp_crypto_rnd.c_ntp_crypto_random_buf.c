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

/* Variables and functions */
 char* ERR_error_string (unsigned long,int /*<<< orphan*/ *) ; 
 unsigned long ERR_get_error () ; 
 int RAND_bytes (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arc4random_buf (void*,size_t) ; 
 int /*<<< orphan*/  size2int_chk (size_t) ; 

int
ntp_crypto_random_buf(
	void *buf,
	size_t nbytes
	)
{
#ifdef USE_OPENSSL_CRYPTO_RAND
	int rc;

	rc = RAND_bytes(buf, size2int_chk(nbytes));
	if (1 != rc) {
		unsigned long err;
		char *err_str;

		err = ERR_get_error();
		err_str = ERR_error_string(err, NULL);
		/* XXX: Log the error */
		(void)&err_str;

		return -1;
	}
	return 0;
#else
	arc4random_buf(buf, nbytes);
	return 0;
#endif
}