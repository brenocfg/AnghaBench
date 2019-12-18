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
 int /*<<< orphan*/  KENV_SET ; 
 int /*<<< orphan*/  KENV_VAR_LEN ; 
 int /*<<< orphan*/  KENV_VAR_NAME ; 
 int /*<<< orphan*/  KENV_VAR_VALUE ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int kenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
priv_kenv_set(int asroot, int injail, struct test *test)
{
	int error;

	error = kenv(KENV_SET, KENV_VAR_NAME, KENV_VAR_VALUE, KENV_VAR_LEN);
	if (asroot && injail)
		expect("priv_kenv_set(asroot, injail)", error, -1, EPERM);
	if (asroot && !injail)
		expect("priv_kenv_set(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_kenv_set(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_kenv_set(!asroot, !injail)", error, -1, EPERM);
}