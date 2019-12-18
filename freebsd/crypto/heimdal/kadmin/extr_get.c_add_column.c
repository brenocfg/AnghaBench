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
struct get_entry_data {int /*<<< orphan*/ * table; int /*<<< orphan*/  extra_mask; int /*<<< orphan*/  mask; struct field_info** ctail; } ;
struct field_name {char const* default_header; int /*<<< orphan*/  flags; int /*<<< orphan*/  fieldvalue; int /*<<< orphan*/  extra_mask; } ;
struct field_info {struct field_info* next; int /*<<< orphan*/ * header; struct field_name* ff; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct field_info* malloc (int) ; 
 int /*<<< orphan*/  rtbl_add_column_by_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static int
add_column(struct get_entry_data *data, struct field_name *ff, const char *header)
{
    struct field_info *f = malloc(sizeof(*f));
    if (f == NULL)
	return ENOMEM;
    f->ff = ff;
    if(header)
	f->header = strdup(header);
    else
	f->header = NULL;
    f->next = NULL;
    *data->ctail = f;
    data->ctail = &f->next;
    data->mask |= ff->fieldvalue;
    data->extra_mask |= ff->extra_mask;
    if(data->table != NULL)
	rtbl_add_column_by_id(data->table, ff->fieldvalue,
			      header ? header : ff->default_header, ff->flags);
    return 0;
}