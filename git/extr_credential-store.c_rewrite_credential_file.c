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
struct credential {int dummy; } ;

/* Variables and functions */
 scalar_t__ commit_lock_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  credential_lock ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 scalar_t__ hold_lock_file_for_update (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_credential_file (char const*,struct credential*,int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (struct strbuf*)) ; 
 int /*<<< orphan*/  print_line (struct strbuf*) ; 

__attribute__((used)) static void rewrite_credential_file(const char *fn, struct credential *c,
				    struct strbuf *extra)
{
	if (hold_lock_file_for_update(&credential_lock, fn, 0) < 0)
		die_errno("unable to get credential storage lock");
	if (extra)
		print_line(extra);
	parse_credential_file(fn, c, NULL, print_line);
	if (commit_lock_file(&credential_lock) < 0)
		die_errno("unable to write credential store");
}