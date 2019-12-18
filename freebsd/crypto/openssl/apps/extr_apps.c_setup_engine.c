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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ENGINE_CTRL_SET_LOGSTREAM ; 
 int /*<<< orphan*/  ENGINE_METHOD_ALL ; 
 int /*<<< orphan*/ * ENGINE_by_id (char const*) ; 
 int /*<<< orphan*/  ENGINE_ctrl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_ctrl_cmd (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 char const* ENGINE_get_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_register_all_complete () ; 
 int /*<<< orphan*/  ENGINE_set_default (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_err ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/ * try_load_engine (char const*) ; 
 int /*<<< orphan*/  ui_method ; 

ENGINE *setup_engine(const char *engine, int debug)
{
    ENGINE *e = NULL;

#ifndef OPENSSL_NO_ENGINE
    if (engine != NULL) {
        if (strcmp(engine, "auto") == 0) {
            BIO_printf(bio_err, "enabling auto ENGINE support\n");
            ENGINE_register_all_complete();
            return NULL;
        }
        if ((e = ENGINE_by_id(engine)) == NULL
            && (e = try_load_engine(engine)) == NULL) {
            BIO_printf(bio_err, "invalid engine \"%s\"\n", engine);
            ERR_print_errors(bio_err);
            return NULL;
        }
        if (debug) {
            ENGINE_ctrl(e, ENGINE_CTRL_SET_LOGSTREAM, 0, bio_err, 0);
        }
        ENGINE_ctrl_cmd(e, "SET_USER_INTERFACE", 0, ui_method, 0, 1);
        if (!ENGINE_set_default(e, ENGINE_METHOD_ALL)) {
            BIO_printf(bio_err, "can't use that engine\n");
            ERR_print_errors(bio_err);
            ENGINE_free(e);
            return NULL;
        }

        BIO_printf(bio_err, "engine \"%s\" set.\n", ENGINE_get_id(e));
    }
#endif
    return e;
}