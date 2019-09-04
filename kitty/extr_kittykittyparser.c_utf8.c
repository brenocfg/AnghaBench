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
typedef  int /*<<< orphan*/  char_type ;

/* Variables and functions */
 int encode_utf8 (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline const char*
utf8(char_type codepoint) {
    if (!codepoint) return "";
    static char buf[8];
    int n = encode_utf8(codepoint, buf);
    buf[n] = 0;
    return buf;
}