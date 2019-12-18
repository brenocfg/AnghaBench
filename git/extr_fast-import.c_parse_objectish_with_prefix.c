#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct branch {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 TYPE_1__ command_buf ; 
 int parse_objectish (struct branch*,char const*) ; 
 int /*<<< orphan*/  skip_prefix (int /*<<< orphan*/ ,char const*,char const**) ; 

__attribute__((used)) static int parse_objectish_with_prefix(struct branch *b, const char *prefix)
{
	const char *base;

	if (!skip_prefix(command_buf.buf, prefix, &base))
		return 0;

	return parse_objectish(b, base);
}