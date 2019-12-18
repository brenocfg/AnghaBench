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
typedef  enum UI_string_types { ____Placeholder_UI_string_types } UI_string_types ;
struct TYPE_4__ {char const* out_string; int input_flags; int type; char* result_buf; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ UI_STRING ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  OUT_STRING_FREEABLE ; 
 int UIT_BOOLEAN ; 
 int UIT_PROMPT ; 
 int UIT_VERIFY ; 
 int /*<<< orphan*/  UI_F_GENERAL_ALLOCATE_PROMPT ; 
 int /*<<< orphan*/  UI_R_NO_RESULT_BUFFER ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UI_STRING *general_allocate_prompt(UI *ui, const char *prompt,
                                          int prompt_freeable,
                                          enum UI_string_types type,
                                          int input_flags, char *result_buf)
{
    UI_STRING *ret = NULL;

    if (prompt == NULL) {
        UIerr(UI_F_GENERAL_ALLOCATE_PROMPT, ERR_R_PASSED_NULL_PARAMETER);
    } else if ((type == UIT_PROMPT || type == UIT_VERIFY
                || type == UIT_BOOLEAN) && result_buf == NULL) {
        UIerr(UI_F_GENERAL_ALLOCATE_PROMPT, UI_R_NO_RESULT_BUFFER);
    } else if ((ret = OPENSSL_malloc(sizeof(*ret))) != NULL) {
        ret->out_string = prompt;
        ret->flags = prompt_freeable ? OUT_STRING_FREEABLE : 0;
        ret->input_flags = input_flags;
        ret->type = type;
        ret->result_buf = result_buf;
    }
    return ret;
}