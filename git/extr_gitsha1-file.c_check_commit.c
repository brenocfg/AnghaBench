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
struct commit {int dummy; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct commit*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ parse_commit_buffer (int /*<<< orphan*/ ,struct commit*,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void check_commit(const void *buf, size_t size)
{
	struct commit c;
	memset(&c, 0, sizeof(c));
	if (parse_commit_buffer(the_repository, &c, buf, size, 0))
		die(_("corrupt commit"));
}