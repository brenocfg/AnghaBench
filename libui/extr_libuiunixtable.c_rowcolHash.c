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
struct rowcol {scalar_t__ col; scalar_t__ row; } ;
typedef  int guint ;
typedef  scalar_t__ gconstpointer ;

/* Variables and functions */

__attribute__((used)) static guint rowcolHash(gconstpointer key)
{
	const struct rowcol *rc = (const struct rowcol *) key;
	guint row, col;

	row = (guint) (rc->row);
	col = (guint) (rc->col);
	return row ^ col;
}