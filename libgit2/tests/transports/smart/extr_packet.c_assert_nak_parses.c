#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_PKT_NAK ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pkt_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_pkt_parse_line (TYPE_1__**,char const**,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void assert_nak_parses(const char *line)
{
	size_t linelen = strlen(line) + 1;
	const char *endptr;
	git_pkt *pkt;

	cl_git_pass(git_pkt_parse_line((git_pkt **) &pkt, &endptr, line, linelen));
	cl_assert_equal_i(pkt->type, GIT_PKT_NAK);
	cl_assert_equal_strn(endptr, line + 7, linelen - 7);

	git_pkt_free((git_pkt *) pkt);
}