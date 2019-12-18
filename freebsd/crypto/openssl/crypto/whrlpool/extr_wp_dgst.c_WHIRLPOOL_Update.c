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
typedef  int /*<<< orphan*/  WHIRLPOOL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  WHIRLPOOL_BitUpdate (int /*<<< orphan*/ *,unsigned char const*,size_t) ; 

int WHIRLPOOL_Update(WHIRLPOOL_CTX *c, const void *_inp, size_t bytes)
{
    /*
     * Well, largest suitable chunk size actually is
     * (1<<(sizeof(size_t)*8-3))-64, but below number is large enough for not
     * to care about excessive calls to WHIRLPOOL_BitUpdate...
     */
    size_t chunk = ((size_t)1) << (sizeof(size_t) * 8 - 4);
    const unsigned char *inp = _inp;

    while (bytes >= chunk) {
        WHIRLPOOL_BitUpdate(c, inp, chunk * 8);
        bytes -= chunk;
        inp += chunk;
    }
    if (bytes)
        WHIRLPOOL_BitUpdate(c, inp, bytes * 8);

    return 1;
}