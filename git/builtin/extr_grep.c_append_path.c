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
struct string_list {int dummy; } ;
struct grep_opt {struct string_list* output_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  string_list_append (struct string_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xstrndup (void const*,size_t) ; 

__attribute__((used)) static void append_path(struct grep_opt *opt, const void *data, size_t len)
{
	struct string_list *path_list = opt->output_priv;

	if (len == 1 && *(const char *)data == '\0')
		return;
	string_list_append(path_list, xstrndup(data, len));
}