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
typedef  int /*<<< orphan*/  ucl_object_t ;
struct ucl_parser {int dummy; } ;

/* Variables and functions */
 int ucl_include_common (unsigned char const*,size_t,int /*<<< orphan*/  const*,struct ucl_parser*,int,int) ; 

bool
ucl_try_include_handler (const unsigned char *data, size_t len,
		const ucl_object_t *args, void* ud)
{
	struct ucl_parser *parser = ud;

	return ucl_include_common (data, len, args, parser, true, false);
}