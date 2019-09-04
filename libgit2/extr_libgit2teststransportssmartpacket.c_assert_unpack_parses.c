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
struct TYPE_2__ {int /*<<< orphan*/  unpack_ok; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_unpack ;
typedef  int /*<<< orphan*/  git_pkt ;

/* Variables and functions */
 int GIT_PKT_UNPACK ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pkt_parse_line (int /*<<< orphan*/ **,char const**,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void assert_unpack_parses(const char *line, bool ok)
{
	size_t linelen = strlen(line) + 1;
	const char *endptr;
	git_pkt_unpack *pkt;

	cl_git_pass(git_pkt_parse_line((git_pkt **) &pkt, &endptr, line, linelen));
	cl_assert_equal_i(pkt->type, GIT_PKT_UNPACK);
	cl_assert_equal_i(pkt->unpack_ok, ok);

	git_pkt_free((git_pkt *) pkt);
}