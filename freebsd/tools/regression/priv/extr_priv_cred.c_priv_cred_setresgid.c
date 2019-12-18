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

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  GID_OTHER ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int setresgid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_cred_setresgid(int asroot, int injail, struct test *test)
{
	int error;

	error = setresgid(GID_OTHER, GID_OTHER, GID_OTHER);
	if (asroot && injail)
		expect("priv_setresgid(asroot, injail)", error, 0, 0);
	if (asroot && !injail)
		expect("priv_setresgid(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_setresgid(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_setresgid(!asroot, !injail)", error, -1, EPERM);
}