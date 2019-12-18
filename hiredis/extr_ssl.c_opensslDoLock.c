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
typedef  int /*<<< orphan*/  sslLockType ;

/* Variables and functions */
 int CRYPTO_LOCK ; 
 int /*<<< orphan*/ * ossl_locks ; 
 int /*<<< orphan*/  sslLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sslLockRelease (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void opensslDoLock(int mode, int lkid, const char *f, int line) {
    sslLockType *l = ossl_locks + lkid;

    if (mode & CRYPTO_LOCK) {
        sslLockAcquire(l);
    } else {
        sslLockRelease(l);
    }

    (void)f;
    (void)line;
}