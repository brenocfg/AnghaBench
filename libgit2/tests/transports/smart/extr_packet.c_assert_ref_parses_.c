#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  oid; } ;
struct TYPE_4__ {int /*<<< orphan*/  capabilities; TYPE_1__ head; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ git_pkt_ref ;
typedef  int /*<<< orphan*/  git_pkt ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_PKT_REF ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_pkt_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pkt_parse_line (int /*<<< orphan*/ **,char const**,char const*,size_t) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void assert_ref_parses_(const char *line, size_t linelen, const char *expected_oid,
	const char *expected_ref, const char *expected_capabilities)
{
	const char *endptr;
	git_pkt_ref *pkt;
	git_oid oid;

	cl_git_pass(git_oid_fromstr(&oid, expected_oid));

	cl_git_pass(git_pkt_parse_line((git_pkt **) &pkt, &endptr, line, linelen));
	cl_assert_equal_i(pkt->type, GIT_PKT_REF);
	cl_assert_equal_oid(&pkt->head.oid, &oid);
	cl_assert_equal_strn(pkt->head.name, expected_ref, strlen(expected_ref));
	if (expected_capabilities)
		cl_assert_equal_strn(pkt->capabilities, expected_capabilities, strlen(expected_capabilities));
	else
		cl_assert_equal_p(NULL, pkt->capabilities);

	git_pkt_free((git_pkt *) pkt);
}