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
struct rowcol {scalar_t__ row; scalar_t__ col; } ;
typedef  scalar_t__ gconstpointer ;
typedef  int gboolean ;

/* Variables and functions */

__attribute__((used)) static gboolean rowcolEqual(gconstpointer a, gconstpointer b)
{
	const struct rowcol *ra = (const struct rowcol *) a;
	const struct rowcol *rb = (const struct rowcol *) b;

	return (ra->row == rb->row) && (ra->col == rb->col);
}