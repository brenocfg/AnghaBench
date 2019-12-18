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
 int UI_add_input_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int UI_add_verify_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UI_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_new () ; 
 int UI_process (int /*<<< orphan*/ *) ; 

int UI_UTIL_read_pw(char *buf, char *buff, int size, const char *prompt,
                    int verify)
{
    int ok = 0;
    UI *ui;

    if (size < 1)
        return -1;

    ui = UI_new();
    if (ui != NULL) {
        ok = UI_add_input_string(ui, prompt, 0, buf, 0, size - 1);
        if (ok >= 0 && verify)
            ok = UI_add_verify_string(ui, prompt, 0, buff, 0, size - 1, buf);
        if (ok >= 0)
            ok = UI_process(ui);
        UI_free(ui);
    }
    if (ok > 0)
        ok = 0;
    return ok;
}