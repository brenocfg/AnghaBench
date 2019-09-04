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
struct am_state {int /*<<< orphan*/  author_date; int /*<<< orphan*/  author_email; int /*<<< orphan*/  author_name; } ;

/* Variables and functions */
 char* am_path (struct am_state*,char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int read_author_script (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_am_author_script(struct am_state *state)
{
	const char *filename = am_path(state, "author-script");

	assert(!state->author_name);
	assert(!state->author_email);
	assert(!state->author_date);

	return read_author_script(filename, &state->author_name,
				  &state->author_email, &state->author_date, 1);
}