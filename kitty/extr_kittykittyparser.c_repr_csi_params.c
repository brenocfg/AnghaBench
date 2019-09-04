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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int snprintf (char*,int,char const*,unsigned int) ; 

__attribute__((used)) static inline const char*
repr_csi_params(unsigned int *params, unsigned int num_params) {
    if (!num_params) return "";
    static char buf[256];
    unsigned int pos = 0;
    while (pos < 200 && num_params && sizeof(buf) > pos + 1) {
        const char *fmt = num_params > 1 ? "%u " : "%u";
        int ret = snprintf(buf + pos, sizeof(buf) - pos - 1, fmt, params[num_params--]);
        if (ret < 0) return "An error occurred formatting the params array";
        pos += ret;
    }
    buf[pos] = 0;
    return buf;
}