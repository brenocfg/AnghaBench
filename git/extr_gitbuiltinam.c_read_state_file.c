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
struct strbuf {int len; } ;
struct am_state {int dummy; } ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  am_path (struct am_state const*,char const*) ; 
 int /*<<< orphan*/  die_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 

__attribute__((used)) static int read_state_file(struct strbuf *sb, const struct am_state *state,
			const char *file, int trim)
{
	strbuf_reset(sb);

	if (strbuf_read_file(sb, am_path(state, file), 0) >= 0) {
		if (trim)
			strbuf_trim(sb);

		return sb->len;
	}

	if (errno == ENOENT)
		return -1;

	die_errno(_("could not read '%s'"), am_path(state, file));
}