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
struct get_entry_data {struct field_info* chead; struct field_info** ctail; } ;
struct field_info {struct field_info* next; struct field_info* header; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct field_info*) ; 

__attribute__((used)) static void
free_columns(struct get_entry_data *data)
{
    struct field_info *f, *next;
    for(f = data->chead; f != NULL; f = next) {
	free(f->header);
	next = f->next;
	free(f);
    }
    data->chead = NULL;
    data->ctail = &data->chead;
}