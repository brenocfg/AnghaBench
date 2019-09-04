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
typedef  int /*<<< orphan*/  uiWindow ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_BUTTONS_OK ; 
 int /*<<< orphan*/  GTK_MESSAGE_ERROR ; 
 int /*<<< orphan*/  msgbox (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowWindow (int /*<<< orphan*/ *) ; 

void uiMsgBoxError(uiWindow *parent, const char *title, const char *description)
{
	msgbox(windowWindow(parent), title, description, GTK_MESSAGE_ERROR, GTK_BUTTONS_OK);
}