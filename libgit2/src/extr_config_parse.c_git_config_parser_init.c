#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* path; int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ git_config_parser ;

/* Variables and functions */
 int git_parse_ctx_init (int /*<<< orphan*/ *,char const*,size_t) ; 

int git_config_parser_init(git_config_parser *out, const char *path, const char *data, size_t datalen)
{
	out->path = path;
	return git_parse_ctx_init(&out->ctx, data, datalen);
}