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
typedef  int /*<<< orphan*/  uiInitOptions ;
struct TYPE_4__ {int /*<<< orphan*/  message; } ;
typedef  TYPE_1__ GError ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  g_direct_equal ; 
 int /*<<< orphan*/  g_direct_hash ; 
 int /*<<< orphan*/  g_error_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 scalar_t__ gtk_init_with_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  timers ; 
 int /*<<< orphan*/  uiprivInitAlloc () ; 
 int /*<<< orphan*/  uiprivLoadFutures () ; 
 int /*<<< orphan*/  uiprivOptions ; 

const char *uiInit(uiInitOptions *o)
{
	GError *err = NULL;
	const char *msg;

	uiprivOptions = *o;
	if (gtk_init_with_args(NULL, NULL, NULL, NULL, NULL, &err) == FALSE) {
		msg = g_strdup(err->message);
		g_error_free(err);
		return msg;
	}
	uiprivInitAlloc();
	uiprivLoadFutures();
	timers = g_hash_table_new(g_direct_hash, g_direct_equal);
	return NULL;
}