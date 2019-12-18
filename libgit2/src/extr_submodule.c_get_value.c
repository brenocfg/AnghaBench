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
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 int git_buf_printf (TYPE_1__*,char*,char const*,char const*) ; 
 int git_config_get_string (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_value(const char **out, git_config *cfg, git_buf *buf, const char *name, const char *field)
{
	int error;

	git_buf_clear(buf);

	if ((error = git_buf_printf(buf, "submodule.%s.%s", name, field)) < 0 ||
	    (error = git_config_get_string(out, cfg, buf->ptr)) < 0)
		return error;

	return error;
}