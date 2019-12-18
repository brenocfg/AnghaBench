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
struct buttonColumnParams {int /*<<< orphan*/  modelColumn; int /*<<< orphan*/  m; } ;
typedef  scalar_t__ gpointer ;
typedef  int /*<<< orphan*/  gchar ;
typedef  int /*<<< orphan*/  GtkCellRenderer ;

/* Variables and functions */
 int /*<<< orphan*/  onEdited (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void buttonColumnClicked(GtkCellRenderer *r, gchar *pathstr, gpointer data)
{
	struct buttonColumnParams *p = (struct buttonColumnParams *) data;

	onEdited(p->m, p->modelColumn, pathstr, NULL, NULL);
}