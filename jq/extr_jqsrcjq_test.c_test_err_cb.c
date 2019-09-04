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
struct err_data {int /*<<< orphan*/  buf; } ;
typedef  int /*<<< orphan*/  jv ;

/* Variables and functions */
 scalar_t__ JV_KIND_STRING ; 
 int /*<<< orphan*/  JV_PRINT_INVALID ; 
 int /*<<< orphan*/  jv_dump_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jv_free (int /*<<< orphan*/ ) ; 
 scalar_t__ jv_get_kind (int /*<<< orphan*/ ) ; 
 char* jv_string_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 char* strchr (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void test_err_cb(void *data, jv e) {
  struct err_data *err_data = data;
  if (jv_get_kind(e) != JV_KIND_STRING)
    e = jv_dump_string(e, JV_PRINT_INVALID);
  if (!strncmp(jv_string_value(e), "jq: error", sizeof("jq: error") - 1))
    snprintf(err_data->buf, sizeof(err_data->buf), "%s", jv_string_value(e));
  if (strchr(err_data->buf, '\n'))
    *(strchr(err_data->buf, '\n')) = '\0';
  jv_free(e);
}