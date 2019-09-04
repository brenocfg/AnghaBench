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
struct TYPE_4__ {char const* buf; size_t len; scalar_t__ pos; } ;
struct TYPE_3__ {TYPE_2__ buf; } ;
struct config_source {int origin_type; char const* name; int /*<<< orphan*/  do_ftell; int /*<<< orphan*/  do_ungetc; int /*<<< orphan*/  do_fgetc; int /*<<< orphan*/  default_error_action; int /*<<< orphan*/ * path; TYPE_1__ u; } ;
struct config_options {int dummy; } ;
typedef  enum config_origin_type { ____Placeholder_config_origin_type } config_origin_type ;
typedef  int /*<<< orphan*/  config_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ERROR_ERROR ; 
 int /*<<< orphan*/  config_buf_fgetc ; 
 int /*<<< orphan*/  config_buf_ftell ; 
 int /*<<< orphan*/  config_buf_ungetc ; 
 int do_config_from (struct config_source*,int /*<<< orphan*/ ,void*,struct config_options const*) ; 

int git_config_from_mem(config_fn_t fn,
			const enum config_origin_type origin_type,
			const char *name, const char *buf, size_t len,
			void *data, const struct config_options *opts)
{
	struct config_source top;

	top.u.buf.buf = buf;
	top.u.buf.len = len;
	top.u.buf.pos = 0;
	top.origin_type = origin_type;
	top.name = name;
	top.path = NULL;
	top.default_error_action = CONFIG_ERROR_ERROR;
	top.do_fgetc = config_buf_fgetc;
	top.do_ungetc = config_buf_ungetc;
	top.do_ftell = config_buf_ftell;

	return do_config_from(&top, fn, data, opts);
}