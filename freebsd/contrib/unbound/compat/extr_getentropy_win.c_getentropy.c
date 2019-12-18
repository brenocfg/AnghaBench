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
typedef  int /*<<< orphan*/  HCRYPTPROV ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPT_VERIFYCONTEXT ; 
 scalar_t__ CryptAcquireContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CryptGenRandom (int /*<<< orphan*/ ,size_t,void*) ; 
 int /*<<< orphan*/  CryptReleaseContext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  PROV_RSA_FULL ; 
 int /*<<< orphan*/  errno ; 

int
getentropy(void *buf, size_t len)
{
	HCRYPTPROV provider;

	if (len > 256) {
		errno = EIO;
		return -1;
	}

	if (CryptAcquireContext(&provider, NULL, NULL, PROV_RSA_FULL,
	    CRYPT_VERIFYCONTEXT) == 0)
		goto fail;
	if (CryptGenRandom(provider, len, buf) == 0) {
		CryptReleaseContext(provider, 0);
		goto fail;
	}
	CryptReleaseContext(provider, 0);
	return (0);

fail:
	errno = EIO;
	return (-1);
}