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
typedef  int /*<<< orphan*/  UI_STRING ;
typedef  int /*<<< orphan*/  UI ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_R_DISABLED ; 
 int /*<<< orphan*/  UI_F_UI_SET_RESULT ; 
 int UI_set_result_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int UI_set_result(UI *ui, UI_STRING *uis, const char *result)
{
#if 0
    /*
     * This is placed here solely to preserve UI_F_UI_SET_RESULT
     * To be removed for OpenSSL 1.2.0
     */
    UIerr(UI_F_UI_SET_RESULT, ERR_R_DISABLED);
#endif
    return UI_set_result_ex(ui, uis, result, strlen(result));
}