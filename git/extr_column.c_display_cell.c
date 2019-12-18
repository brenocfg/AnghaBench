#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* indent; char const* nl; scalar_t__ padding; } ;
struct column_data {int* len; size_t* width; int rows; int cols; TYPE_3__* list; TYPE_1__ opts; int /*<<< orphan*/  colopts; } ;
struct TYPE_6__ {int nr; TYPE_2__* items; } ;
struct TYPE_5__ {char* string; } ;

/* Variables and functions */
 scalar_t__ COL_COLUMN ; 
 scalar_t__ COL_LAYOUT (int /*<<< orphan*/ ) ; 
 int XY2LINEAR (struct column_data*,int,int) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char const*) ; 

__attribute__((used)) static int display_cell(struct column_data *data, int initial_width,
			const char *empty_cell, int x, int y)
{
	int i, len, newline;

	i = XY2LINEAR(data, x, y);
	if (i >= data->list->nr)
		return -1;

	len = data->len[i];
	if (data->width && data->len[data->width[x]] < initial_width) {
		/*
		 * empty_cell has initial_width chars, if real column
		 * is narrower, increase len a bit so we fill less
		 * space.
		 */
		len += initial_width - data->len[data->width[x]];
		len -= data->opts.padding;
	}

	if (COL_LAYOUT(data->colopts) == COL_COLUMN)
		newline = i + data->rows >= data->list->nr;
	else
		newline = x == data->cols - 1 || i == data->list->nr - 1;

	printf("%s%s%s",
	       x == 0 ? data->opts.indent : "",
	       data->list->items[i].string,
	       newline ? data->opts.nl : empty_cell + len);
	return 0;
}