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
typedef  scalar_t__ text_t ;
typedef  size_t len_t ;

/* Variables and functions */

__attribute__((used)) static inline bool
has_char(text_t *text, len_t sz, text_t ch) {
    for(len_t i = 0; i < sz; i++) {
        if(text[i] == ch) return true;
    }
    return false;
}