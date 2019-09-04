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
typedef  unsigned char uint32_t ;

/* Variables and functions */
 size_t strlen (char const*) ; 

__attribute__((used)) static inline bool
startswith(const uint32_t *string, size_t sz, const char *prefix) {
    size_t l = strlen(prefix);
    if (sz < l) return false;
    for (size_t i = 0; i < l; i++) {
        if (string[i] != (unsigned char)prefix[i]) return false;
    }
    return true;
}