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
struct test {int dummy; } ;
typedef  int /*<<< orphan*/  record ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  MAX_AUDIT_RECORD_SIZE ; 
 int audit (char*,int) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 

void
priv_audit_submit(int asroot, int injail, struct test *test)
{
	char record[MAX_AUDIT_RECORD_SIZE+10];
	int error;

	bzero(record, sizeof(record));
	error = audit(record, sizeof(record));
	if (asroot && injail)
		expect("priv_audit_submit(asroot, injail)", error, -1,
		    ENOSYS);
	if (asroot && !injail)
		expect("priv_audit_submit(asroot, !injail)", error, -1,
		    EINVAL);
	if (!asroot && injail)
		expect("priv_audit_submit(!asroot, injail)", error, -1,
		    ENOSYS);
	if (!asroot && !injail)
		expect("priv_audit_submit(!asroot, !injail)", error, -1,
		    EPERM);
}