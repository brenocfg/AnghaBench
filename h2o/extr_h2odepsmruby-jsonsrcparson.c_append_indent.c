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
 int /*<<< orphan*/  APPEND_STRING (char*) ; 

__attribute__((used)) static int append_indent(char *buf, int level) {
    int i;
    int written = -1, written_total = 0;
    for (i = 0; i < level; i++) {
        APPEND_STRING("    ");
    }
    return written_total;
}