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
 int /*<<< orphan*/  CHECK_EOF () ; 
 int /*<<< orphan*/  EXPECT_CHAR (char) ; 

__attribute__((used)) static const char *is_complete(const char *buf, const char *buf_end, size_t last_len, int *ret)
{
    int ret_cnt = 0;
    buf = last_len < 3 ? buf : buf + last_len - 3;

    while (1) {
        CHECK_EOF();
        if (*buf == '\015') {
            ++buf;
            CHECK_EOF();
            EXPECT_CHAR('\012');
            ++ret_cnt;
        } else if (*buf == '\012') {
            ++buf;
            ++ret_cnt;
        } else {
            ++buf;
            ret_cnt = 0;
        }
        if (ret_cnt == 2) {
            return buf;
        }
    }

    *ret = -2;
    return NULL;
}