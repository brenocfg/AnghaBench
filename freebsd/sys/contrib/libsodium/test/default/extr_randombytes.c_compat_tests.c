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
 scalar_t__* freq ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  randombytes (scalar_t__*,int) ; 
 scalar_t__* x ; 

__attribute__((used)) static int
compat_tests(void)
{
    size_t i;

    memset(x, 0, sizeof x);
    randombytes(x, sizeof x);
    for (i = 0; i < 256; ++i) {
        freq[i] = 0;
    }
    for (i = 0; i < sizeof x; ++i) {
        ++freq[255 & (int) x[i]];
    }
    for (i = 0; i < 256; ++i) {
        if (!freq[i]) {
            printf("nacl_tests failed\n");
        }
    }
    return 0;
}