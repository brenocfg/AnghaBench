#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  text_t ;
struct TYPE_3__ {int /*<<< orphan*/  level3_len; int /*<<< orphan*/  level3; int /*<<< orphan*/  level2_len; int /*<<< orphan*/  level2; int /*<<< orphan*/  level1_len; int /*<<< orphan*/  level1; } ;
typedef  TYPE_1__ WorkSpace ;

/* Variables and functions */
 scalar_t__ IS_LOWERCASE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_UPPERCASE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOWERCASE (int /*<<< orphan*/ ) ; 
 scalar_t__ has_char (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint8_t
level_factor_for(text_t current, text_t last, WorkSpace *w) {
    text_t lch = LOWERCASE(last);
    if (has_char(w->level1, w->level1_len, lch)) return 90;
    if (has_char(w->level2, w->level2_len, lch)) return 80;
    if (IS_LOWERCASE(last) && IS_UPPERCASE(current)) return 80; // CamelCase
    if (has_char(w->level3, w->level3_len, lch)) return 70;
    return 0;
}