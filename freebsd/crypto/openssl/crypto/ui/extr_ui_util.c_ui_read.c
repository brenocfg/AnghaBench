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
struct pem_password_cb_data {int (* cb ) (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  rwflag; } ;
typedef  int /*<<< orphan*/  UI_STRING ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int PEM_BUFSIZE ; 
#define  UIT_BOOLEAN 133 
#define  UIT_ERROR 132 
#define  UIT_INFO 131 
#define  UIT_NONE 130 
#define  UIT_PROMPT 129 
#define  UIT_VERIFY 128 
 int /*<<< orphan*/  UI_get0_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UI_get_method (int /*<<< orphan*/ *) ; 
 int UI_get_result_maxsize (int /*<<< orphan*/ *) ; 
 int UI_get_string_type (int /*<<< orphan*/ *) ; 
 struct pem_password_cb_data* UI_method_get_ex_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UI_set_result_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int stub1 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ui_method_data_index ; 

__attribute__((used)) static int ui_read(UI *ui, UI_STRING *uis)
{
    switch (UI_get_string_type(uis)) {
    case UIT_PROMPT:
        {
            char result[PEM_BUFSIZE + 1];
            const struct pem_password_cb_data *data =
                UI_method_get_ex_data(UI_get_method(ui), ui_method_data_index);
            int maxsize = UI_get_result_maxsize(uis);
            int len = data->cb(result,
                               maxsize > PEM_BUFSIZE ? PEM_BUFSIZE : maxsize,
                               data->rwflag, UI_get0_user_data(ui));

            if (len >= 0)
                result[len] = '\0';
            if (len <= 0)
                return len;
            if (UI_set_result_ex(ui, uis, result, len) >= 0)
                return 1;
            return 0;
        }
    case UIT_VERIFY:
    case UIT_NONE:
    case UIT_BOOLEAN:
    case UIT_INFO:
    case UIT_ERROR:
        break;
    }
    return 1;
}