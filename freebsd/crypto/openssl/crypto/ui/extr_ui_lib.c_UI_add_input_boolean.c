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
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  UIT_BOOLEAN ; 
 int general_allocate_boolean (int /*<<< orphan*/ *,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 

int UI_add_input_boolean(UI *ui, const char *prompt, const char *action_desc,
                         const char *ok_chars, const char *cancel_chars,
                         int flags, char *result_buf)
{
    return general_allocate_boolean(ui, prompt, action_desc,
                                    ok_chars, cancel_chars, 0, UIT_BOOLEAN,
                                    flags, result_buf);
}