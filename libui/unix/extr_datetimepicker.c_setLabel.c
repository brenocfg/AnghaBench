#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ hasDate; scalar_t__ hasTime; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  scalar_t__ gboolean ;
typedef  int /*<<< orphan*/  GDateTime ;

/* Variables and functions */
 int /*<<< orphan*/  D_FMT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GTK_BUTTON (TYPE_1__*) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  T_FMT ; 
 char* g_date_time_format (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_date_time_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup_printf (char*,char*,char*) ; 
 int /*<<< orphan*/  gtk_button_set_label (int /*<<< orphan*/ ,char*) ; 
 char* nl_langinfo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * selected (TYPE_1__*) ; 

__attribute__((used)) static void setLabel(uiprivDateTimePickerWidget *d)
{
	GDateTime *dt;
	char *fmt;
	char *msg;
	gboolean free;

	dt = selected(d);
	free = FALSE;
	if (d->hasDate && d->hasTime) {
		// don't use D_T_FMT; that's too verbose
		fmt = g_strdup_printf("%s %s", nl_langinfo(D_FMT), nl_langinfo(T_FMT));
		free = TRUE;
	} else if (d->hasDate)
		fmt = nl_langinfo(D_FMT);
	else
		fmt = nl_langinfo(T_FMT);
	msg = g_date_time_format(dt, fmt);
	gtk_button_set_label(GTK_BUTTON(d), msg);
	g_free(msg);
	if (free)
		g_free(fmt);
	g_date_time_unref(dt);
}