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
typedef  int /*<<< orphan*/  CanonicalFromStringResult ;

/* Variables and functions */
 int /*<<< orphan*/  CanonicalFromString_invalidFormat ; 
 int /*<<< orphan*/  CanonicalFromString_ok ; 
 int charToHex (char const) ; 

__attribute__((used)) static CanonicalFromStringResult canonicalFromString(unsigned char* dst,
                                                     size_t dstSize,
                                                     const char* hashStr)
{
    size_t i;
    for (i = 0; i < dstSize; ++i) {
        int h0, h1;

        h0 = charToHex(hashStr[i*2 + 0]);
        if (h0 < 0) return CanonicalFromString_invalidFormat;

        h1 = charToHex(hashStr[i*2 + 1]);
        if (h1 < 0) return CanonicalFromString_invalidFormat;

        dst[i] = (unsigned char) ((h0 << 4) | h1);
    }
    return CanonicalFromString_ok;
}