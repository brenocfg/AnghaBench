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
 int /*<<< orphan*/  EXPECT_CHAR (char) ; 
 char const* parse_int (char const*,char const*,int*,int*) ; 

__attribute__((used)) static const char *parse_http_version(const char *buf, const char *buf_end, int *minor_version, int *ret)
{
    EXPECT_CHAR('H');
    EXPECT_CHAR('T');
    EXPECT_CHAR('T');
    EXPECT_CHAR('P');
    EXPECT_CHAR('/');
    EXPECT_CHAR('1');
    EXPECT_CHAR('.');
    return parse_int(buf, buf_end, minor_version, ret);
}