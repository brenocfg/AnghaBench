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
typedef  int char_type ;

/* Variables and functions */

__attribute__((used)) static inline bool
is_private_use(char_type ch) {
    return (0xe000 <= ch && ch <= 0xf8ff) || (0xF0000 <= ch && ch <= 0xFFFFF) || (0x100000 <= ch && ch <= 0x10FFFF);
}