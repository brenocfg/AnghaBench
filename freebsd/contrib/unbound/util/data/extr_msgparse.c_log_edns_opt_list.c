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
struct edns_option {struct edns_option* next; int /*<<< orphan*/  opt_len; int /*<<< orphan*/  opt_data; int /*<<< orphan*/  opt_code; } ;
typedef  int /*<<< orphan*/  str ;
typedef  enum verbosity_value { ____Placeholder_verbosity_value } verbosity_value ;

/* Variables and functions */
 int /*<<< orphan*/  sldns_wire2str_edns_option_print (char**,size_t*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int,char*,char const*) ; 
 int verbosity ; 

void
log_edns_opt_list(enum verbosity_value level, const char* info_str,
	struct edns_option* list)
{
	if(verbosity >= level && list) {
		char str[128], *s;
		size_t slen;
		verbose(level, "%s", info_str);
		while(list) {
			s = str;
			slen = sizeof(str);
			(void)sldns_wire2str_edns_option_print(&s, &slen, list->opt_code,
				list->opt_data, list->opt_len);
			verbose(level, "  %s", str);
			list = list->next;
		}
	}
}