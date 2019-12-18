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
struct string_list {int nr; TYPE_1__* items; } ;
struct TYPE_4__ {char* buf; int len; } ;
struct TYPE_3__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 char* find_header (char const*,int,char*,char const**) ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_2__ push_cert ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int check_cert_push_options(const struct string_list *push_options)
{
	const char *buf = push_cert.buf;
	int len = push_cert.len;

	char *option;
	const char *next_line;
	int options_seen = 0;

	int retval = 1;

	if (!len)
		return 1;

	while ((option = find_header(buf, len, "push-option", &next_line))) {
		len -= (next_line - buf);
		buf = next_line;
		options_seen++;
		if (options_seen > push_options->nr
		    || strcmp(option,
			      push_options->items[options_seen - 1].string)) {
			retval = 0;
			goto leave;
		}
		free(option);
	}

	if (options_seen != push_options->nr)
		retval = 0;

leave:
	free(option);
	return retval;
}