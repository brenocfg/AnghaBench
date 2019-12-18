#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UI ;
struct TYPE_4__ {char* prompt_info; } ;
typedef  TYPE_1__ PW_CB_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_cleanse (char*,unsigned int) ; 
 int /*<<< orphan*/  OPENSSL_clear_free (char*,unsigned int) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  PW_MIN_LENGTH ; 
 int /*<<< orphan*/  UI_CTRL_IS_REDOABLE ; 
 int /*<<< orphan*/  UI_CTRL_PRINT_ERRORS ; 
 int UI_INPUT_FLAG_DEFAULT_PWD ; 
 int UI_add_input_string (int /*<<< orphan*/ *,char*,int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UI_add_user_data (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int UI_add_verify_string (int /*<<< orphan*/ *,char*,int,char*,int /*<<< orphan*/ ,int,char*) ; 
 char* UI_construct_prompt (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ UI_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * UI_new_method (int /*<<< orphan*/ ) ; 
 int UI_process (int /*<<< orphan*/ *) ; 
 char* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  ui_method ; 

int password_callback(char *buf, int bufsiz, int verify, PW_CB_DATA *cb_tmp)
{
    int res = 0;
    UI *ui = NULL;
    PW_CB_DATA *cb_data = (PW_CB_DATA *)cb_tmp;

    ui = UI_new_method(ui_method);
    if (ui) {
        int ok = 0;
        char *buff = NULL;
        int ui_flags = 0;
        const char *prompt_info = NULL;
        char *prompt;

        if (cb_data != NULL && cb_data->prompt_info != NULL)
            prompt_info = cb_data->prompt_info;
        prompt = UI_construct_prompt(ui, "pass phrase", prompt_info);
        if (!prompt) {
            BIO_printf(bio_err, "Out of memory\n");
            UI_free(ui);
            return 0;
        }

        ui_flags |= UI_INPUT_FLAG_DEFAULT_PWD;
        UI_ctrl(ui, UI_CTRL_PRINT_ERRORS, 1, 0, 0);

        /* We know that there is no previous user data to return to us */
        (void)UI_add_user_data(ui, cb_data);

        ok = UI_add_input_string(ui, prompt, ui_flags, buf,
                                 PW_MIN_LENGTH, bufsiz - 1);

        if (ok >= 0 && verify) {
            buff = app_malloc(bufsiz, "password buffer");
            ok = UI_add_verify_string(ui, prompt, ui_flags, buff,
                                      PW_MIN_LENGTH, bufsiz - 1, buf);
        }
        if (ok >= 0)
            do {
                ok = UI_process(ui);
            } while (ok < 0 && UI_ctrl(ui, UI_CTRL_IS_REDOABLE, 0, 0, 0));

        OPENSSL_clear_free(buff, (unsigned int)bufsiz);

        if (ok >= 0)
            res = strlen(buf);
        if (ok == -1) {
            BIO_printf(bio_err, "User interface error\n");
            ERR_print_errors(bio_err);
            OPENSSL_cleanse(buf, (unsigned int)bufsiz);
            res = 0;
        }
        if (ok == -2) {
            BIO_printf(bio_err, "aborted!\n");
            OPENSSL_cleanse(buf, (unsigned int)bufsiz);
            res = 0;
        }
        UI_free(ui);
        OPENSSL_free(prompt);
    }
    return res;
}