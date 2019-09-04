#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int /*<<< orphan*/  indent; scalar_t__ padding; } ;
struct column_data {int* len; int cols; TYPE_2__* list; int /*<<< orphan*/  rows; TYPE_1__ opts; } ;
struct TYPE_4__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void layout(struct column_data *data, int *width)
{
	int i;

	*width = 0;
	for (i = 0; i < data->list->nr; i++)
		if (*width < data->len[i])
			*width = data->len[i];

	*width += data->opts.padding;

	data->cols = (data->opts.width - strlen(data->opts.indent)) / *width;
	if (data->cols == 0)
		data->cols = 1;

	data->rows = DIV_ROUND_UP(data->list->nr, data->cols);
}