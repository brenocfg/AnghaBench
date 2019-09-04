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
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  git_path_bisect_expected_rev () ; 
 int strbuf_read_file (struct strbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_trim (struct strbuf*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int is_expected_rev(const char *expected_hex)
{
	struct strbuf actual_hex = STRBUF_INIT;
	int res = 0;
	if (strbuf_read_file(&actual_hex, git_path_bisect_expected_rev(), 0) >= 40) {
		strbuf_trim(&actual_hex);
		res = !strcmp(actual_hex.buf, expected_hex);
	}
	strbuf_release(&actual_hex);
	return res;
}