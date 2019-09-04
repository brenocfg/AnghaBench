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
struct tablePart {int /*<<< orphan*/  textColumn; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkCellRendererText ;

/* Variables and functions */
 int /*<<< orphan*/  onEdited (struct tablePart*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void textEdited(GtkCellRendererText *renderer, gchar *path, gchar *newText, gpointer data)
{
	struct tablePart *part = (struct tablePart *) data;

	onEdited(part, part->textColumn, path, newText);
}