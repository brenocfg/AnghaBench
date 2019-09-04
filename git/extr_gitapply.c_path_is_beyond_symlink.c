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
struct strbuf {int dummy; } ;
struct apply_state {int dummy; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  assert (int) ; 
 int path_is_beyond_symlink_1 (struct apply_state*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

__attribute__((used)) static int path_is_beyond_symlink(struct apply_state *state, const char *name_)
{
	int ret;
	struct strbuf name = STRBUF_INIT;

	assert(*name_ != '\0');
	strbuf_addstr(&name, name_);
	ret = path_is_beyond_symlink_1(state, &name);
	strbuf_release(&name);

	return ret;
}