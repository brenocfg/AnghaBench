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
typedef  scalar_t__ BYTE ;

/* Variables and functions */

__attribute__((used)) static int ZSTD_isRLE(const BYTE *ip, size_t length) {
    size_t i;
    if (length < 2) return 1;
    for (i = 1; i < length; ++i) {
        if (ip[0] != ip[i]) return 0;
    }
    return 1;
}