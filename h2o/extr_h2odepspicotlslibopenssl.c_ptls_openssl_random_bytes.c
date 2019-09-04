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
 int RAND_bytes (void*,int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

void ptls_openssl_random_bytes(void *buf, size_t len)
{
    int ret = RAND_bytes(buf, (int)len);
    if (ret != 1) {
        fprintf(stderr, "RAND_bytes() failed with code: %d\n", ret);
        abort();
    }
}