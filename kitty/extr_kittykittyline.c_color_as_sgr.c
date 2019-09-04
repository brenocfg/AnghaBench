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
 int snprintf (char*,size_t,char*,unsigned int,...) ; 

__attribute__((used)) static inline int
color_as_sgr(char *buf, size_t sz, unsigned long val, unsigned simple_code, unsigned aix_code, unsigned complex_code) {
    switch(val & 0xff) {
        case 1:
            val >>= 8;
            if (val < 16 && simple_code) {
                return snprintf(buf, sz, "%lu;", (val < 8) ? simple_code + val : aix_code + (val - 8));
            }
            return snprintf(buf, sz, "%u:5:%lu;", complex_code, val);
        case 2:
            return snprintf(buf, sz, "%u:2:%lu:%lu:%lu;", complex_code, (val >> 24) & 0xff, (val >> 16) & 0xff, (val >> 8) & 0xff);
        default:
            return snprintf(buf, sz, "%u;", complex_code + 1);  // reset
    }
}