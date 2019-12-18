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
typedef  int /*<<< orphan*/  ldns_rr_list ;
struct TYPE_5__ {int flags; } ;
typedef  TYPE_1__ ldns_output_format ;
typedef  int /*<<< orphan*/  ldns_buffer ;

/* Variables and functions */
 int LDNS_COMMENT_NULLS ; 
 int /*<<< orphan*/  LDNS_MAX_PACKETLEN ; 
 scalar_t__ LDNS_STATUS_OK ; 
 char* ldns_buffer_export2str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ldns_buffer_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ldns_buffer_printf (int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* ldns_output_format_default ; 
 scalar_t__ ldns_rr_list2buffer_str_fmt (int /*<<< orphan*/ *,TYPE_1__ const*,int /*<<< orphan*/  const*) ; 

char *
ldns_rr_list2str_fmt(const ldns_output_format *fmt, const ldns_rr_list *list)
{
	char *result = NULL;
	ldns_buffer *tmp_buffer = ldns_buffer_new(LDNS_MAX_PACKETLEN);

	if (!tmp_buffer) {
		return NULL;
	}
	if (list) {
		if (ldns_rr_list2buffer_str_fmt(
				   tmp_buffer, fmt, list)
			       	== LDNS_STATUS_OK) {
		}
	} else {
		if (fmt == NULL) {
			fmt = ldns_output_format_default;
		}
		if (fmt->flags & LDNS_COMMENT_NULLS) {
			ldns_buffer_printf(tmp_buffer, "; (null)\n");
		}
	}

	/* export and return string, destroy rest */
	result = ldns_buffer_export2str(tmp_buffer);
	ldns_buffer_free(tmp_buffer);
	return result;
}