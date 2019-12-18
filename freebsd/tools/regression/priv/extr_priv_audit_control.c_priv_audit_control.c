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
typedef  int /*<<< orphan*/  policy ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETPOLICY ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 int auditon (int /*<<< orphan*/ ,long*,int) ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 

void
priv_audit_control(int asroot, int injail, struct test *test)
{
	long policy;
	int error;

	error = auditon(A_GETPOLICY, &policy, sizeof(policy));
	if (asroot && injail)
		expect("priv_audit_control(asroot, injail)", error, -1,
		    ENOSYS);
	if (asroot && !injail)
		expect("priv_audit_control(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_audit_control(!asroot, injail)", error, -1,
		    ENOSYS);
	if (!asroot && !injail)
		expect("priv_audit_control(!asroot, !injail)", error, -1,
		    EPERM);
}