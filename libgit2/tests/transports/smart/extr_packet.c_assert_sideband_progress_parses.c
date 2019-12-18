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
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_progress ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 size_t GIT_PKT_PROGRESS ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pkt_parse_line (int /*<<< orphan*/ **,char const**,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void assert_sideband_progress_parses(const char *line, const char *expected_data, size_t expected_len)
{
	size_t linelen = strlen(line) + 1;
	const char *endptr;
	git_pkt_progress *pkt;

	cl_git_pass(git_pkt_parse_line((git_pkt **) &pkt, &endptr, line, linelen));
	cl_assert_equal_i(pkt->type, GIT_PKT_PROGRESS);
	cl_assert_equal_i(pkt->len, expected_len);
	cl_assert_equal_strn(pkt->data, expected_data, expected_len);

	git_pkt_free((git_pkt *) pkt);
}