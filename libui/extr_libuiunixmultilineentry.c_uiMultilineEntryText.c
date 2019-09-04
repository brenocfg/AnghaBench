#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  textbuf; } ;
typedef  TYPE_1__ uiMultilineEntry ;
typedef  int /*<<< orphan*/  GtkTextIter ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  gtk_text_buffer_get_end_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_text_buffer_get_start_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* gtk_text_buffer_get_text (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* uiUnixStrdupText (char*) ; 

char *uiMultilineEntryText(uiMultilineEntry *e)
{
	GtkTextIter start, end;
	char *tret, *out;

	gtk_text_buffer_get_start_iter(e->textbuf, &start);
	gtk_text_buffer_get_end_iter(e->textbuf, &end);
	tret = gtk_text_buffer_get_text(e->textbuf, &start, &end, TRUE);
	// theoretically we could just return tret because uiUnixStrdupText() is just g_strdup(), but if that ever changes we can't, so let's do it this way to be safe
	out = uiUnixStrdupText(tret);
	g_free(tret);
	return out;
}