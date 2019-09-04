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
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_iovec_init (char const*,int) ; 
 int /*<<< orphan*/  is_ws (char const) ; 

h2o_iovec_t h2o_str_stripws(const char *s, size_t len)
{
    const char *end = s + len;

    while (s != end) {
        if (!is_ws(*s))
            break;
        ++s;
    }
    while (s != end) {
        if (!is_ws(end[-1]))
            break;
        --end;
    }
    return h2o_iovec_init(s, end - s);
}