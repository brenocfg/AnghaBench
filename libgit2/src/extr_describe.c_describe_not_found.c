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
typedef  int /*<<< orphan*/  oid_str ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_DESCRIBE ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char const*,char*) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int describe_not_found(const git_oid *oid, const char *message_format) {
	char oid_str[GIT_OID_HEXSZ + 1];
	git_oid_tostr(oid_str, sizeof(oid_str), oid);

	git_error_set(GIT_ERROR_DESCRIBE, message_format, oid_str);
	return GIT_ENOTFOUND;
}