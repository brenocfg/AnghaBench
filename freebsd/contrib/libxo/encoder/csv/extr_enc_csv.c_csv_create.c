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
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_5__ {int /*<<< orphan*/  c_stack_buf; int /*<<< orphan*/  c_value_buf; int /*<<< orphan*/  c_name_buf; int /*<<< orphan*/  c_data; } ;
typedef  TYPE_1__ csv_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xo_buf_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* xo_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xo_set_private (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
csv_create (xo_handle_t *xop)
{
    csv_private_t *csv = xo_realloc(NULL, sizeof(*csv));
    if (csv == NULL)
	return -1;

    bzero(csv, sizeof(*csv));
    xo_buf_init(&csv->c_data);
    xo_buf_init(&csv->c_name_buf);
    xo_buf_init(&csv->c_value_buf);
#ifdef CSV_STACK_IS_NEEDED
    xo_buf_init(&csv->c_stack_buf);
#endif /* CSV_STACK_IS_NEEDED */

    xo_set_private(xop, csv);

    return 0;
}