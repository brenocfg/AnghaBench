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
struct TYPE_2__ {int /*<<< orphan*/  status; int /*<<< orphan*/  oid; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_pkt_ack ;
typedef  int /*<<< orphan*/  git_pkt ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  enum git_ack_status { ____Placeholder_git_ack_status } git_ack_status ;

/* Variables and functions */
 int GIT_PKT_ACK ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pkt_parse_line (int /*<<< orphan*/ **,char const**,char const*,size_t) ; 
 int strlen (char const*) ; 

__attribute__((used)) static void assert_ack_parses(const char *line, const char *expected_oid, enum git_ack_status expected_status)
{
	size_t linelen = strlen(line) + 1;
	const char *endptr;
	git_pkt_ack *pkt;
	git_oid oid;

	cl_git_pass(git_oid_fromstr(&oid, expected_oid));

	cl_git_pass(git_pkt_parse_line((git_pkt **) &pkt, &endptr, line, linelen));
	cl_assert_equal_i(pkt->type, GIT_PKT_ACK);
	cl_assert_equal_oid(&pkt->oid, &oid);
	cl_assert_equal_i(pkt->status, expected_status);

	git_pkt_free((git_pkt *) pkt);
}