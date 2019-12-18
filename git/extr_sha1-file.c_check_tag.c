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
typedef  int /*<<< orphan*/  t ;
struct tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tag*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_tag_buffer (int /*<<< orphan*/ ,struct tag*,void const*,size_t) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void check_tag(const void *buf, size_t size)
{
	struct tag t;
	memset(&t, 0, sizeof(t));
	if (parse_tag_buffer(the_repository, &t, buf, size))
		die(_("corrupt tag"));
}