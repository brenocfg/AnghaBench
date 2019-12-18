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
struct status_block {int /*<<< orphan*/  full_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  I3STRING_FREE (int /*<<< orphan*/ ) ; 
 struct status_block* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i3string_from_utf8 (char*) ; 
 int /*<<< orphan*/  statusline_head ; 

__attribute__((used)) static void read_flat_input(char *buffer, int length) {
    struct status_block *first = TAILQ_FIRST(&statusline_head);
    /* Clear the old buffer if any. */
    I3STRING_FREE(first->full_text);
    /* Remove the trailing newline and terminate the string at the same
     * time. */
    if (buffer[length - 1] == '\n' || buffer[length - 1] == '\r') {
        buffer[length - 1] = '\0';
    } else {
        buffer[length] = '\0';
    }

    first->full_text = i3string_from_utf8(buffer);
}