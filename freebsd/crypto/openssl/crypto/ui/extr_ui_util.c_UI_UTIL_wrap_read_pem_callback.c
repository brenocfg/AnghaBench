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
struct pem_password_cb_data {int rwflag; int /*<<< orphan*/ * cb; } ;
typedef  int /*<<< orphan*/  pem_password_cb ;
typedef  int /*<<< orphan*/  UI_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (struct pem_password_cb_data*) ; 
 struct pem_password_cb_data* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  RUN_ONCE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * UI_create_method (char*) ; 
 int /*<<< orphan*/  UI_destroy_method (int /*<<< orphan*/ *) ; 
 scalar_t__ UI_method_set_closer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ UI_method_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pem_password_cb_data*) ; 
 scalar_t__ UI_method_set_opener (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ UI_method_set_reader (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ UI_method_set_writer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_index_once ; 
 int /*<<< orphan*/  ui_close ; 
 int /*<<< orphan*/  ui_method_data_index ; 
 int /*<<< orphan*/  ui_method_data_index_init ; 
 int /*<<< orphan*/  ui_open ; 
 int /*<<< orphan*/  ui_read ; 
 int /*<<< orphan*/  ui_write ; 

UI_METHOD *UI_UTIL_wrap_read_pem_callback(pem_password_cb *cb, int rwflag)
{
    struct pem_password_cb_data *data = NULL;
    UI_METHOD *ui_method = NULL;

    if ((data = OPENSSL_zalloc(sizeof(*data))) == NULL
        || (ui_method = UI_create_method("PEM password callback wrapper")) == NULL
        || UI_method_set_opener(ui_method, ui_open) < 0
        || UI_method_set_reader(ui_method, ui_read) < 0
        || UI_method_set_writer(ui_method, ui_write) < 0
        || UI_method_set_closer(ui_method, ui_close) < 0
        || !RUN_ONCE(&get_index_once, ui_method_data_index_init)
        || UI_method_set_ex_data(ui_method, ui_method_data_index, data) < 0) {
        UI_destroy_method(ui_method);
        OPENSSL_free(data);
        return NULL;
    }
    data->rwflag = rwflag;
    data->cb = cb;

    return ui_method;
}