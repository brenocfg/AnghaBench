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
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gidset ; 
 int /*<<< orphan*/  gidset_len ; 
 int setgroups (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_cred_setgroups(int asroot, int injail, struct test *test)
{
	int error;

	error = setgroups(gidset_len, gidset);
	if (asroot && injail)
		expect("priv_setgroups(asroot, injail)", error, 0, 0);
	if (asroot && !injail)
		expect("priv_setgroups(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_setgroups(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_setgroups(!asroot, !injail)", error, -1, EPERM);
}