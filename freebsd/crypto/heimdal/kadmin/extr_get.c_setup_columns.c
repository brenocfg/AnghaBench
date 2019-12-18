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
struct get_entry_data {int dummy; } ;
struct field_name {int /*<<< orphan*/ * fieldname; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  add_column (struct get_entry_data*,struct field_name*,char*) ; 
 int /*<<< orphan*/  context ; 
 struct field_name* field_names ; 
 int /*<<< orphan*/  free_columns (struct get_entry_data*) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ strcasecmp (char*,int /*<<< orphan*/ *) ; 
 char* strsep (char**,char*) ; 
 int strsep_copy (char const**,char*,char*,int) ; 

__attribute__((used)) static int
setup_columns(struct get_entry_data *data, const char *column_info)
{
    char buf[1024], *q;
    char *field, *header;
    struct field_name *f;

    while(strsep_copy(&column_info, ",", buf, sizeof(buf)) != -1) {
	q = buf;
	field = strsep(&q, "=");
	header = strsep(&q, "=");
	for(f = field_names; f->fieldname != NULL; f++) {
	    if(strcasecmp(field, f->fieldname) == 0) {
		add_column(data, f, header);
		break;
	    }
	}
	if(f->fieldname == NULL) {
	    krb5_warnx(context, "unknown field name \"%s\"", field);
	    free_columns(data);
	    return -1;
	}
    }
    return 0;
}