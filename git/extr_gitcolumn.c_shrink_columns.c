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
struct TYPE_4__ {int width; scalar_t__ padding; int /*<<< orphan*/  indent; } ;
struct column_data {size_t* width; int cols; int rows; TYPE_2__ opts; scalar_t__* len; TYPE_1__* list; } ;
struct TYPE_3__ {int /*<<< orphan*/  nr; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REALLOC_ARRAY (size_t*,int) ; 
 int /*<<< orphan*/  compute_column_width (struct column_data*) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shrink_columns(struct column_data *data)
{
	REALLOC_ARRAY(data->width, data->cols);
	while (data->rows > 1) {
		int x, total_width, cols, rows;
		rows = data->rows;
		cols = data->cols;

		data->rows--;
		data->cols = DIV_ROUND_UP(data->list->nr, data->rows);
		if (data->cols != cols)
			REALLOC_ARRAY(data->width, data->cols);
		compute_column_width(data);

		total_width = strlen(data->opts.indent);
		for (x = 0; x < data->cols; x++) {
			total_width += data->len[data->width[x]];
			total_width += data->opts.padding;
		}
		if (total_width > data->opts.width) {
			data->rows = rows;
			data->cols = cols;
			break;
		}
	}
	compute_column_width(data);
}