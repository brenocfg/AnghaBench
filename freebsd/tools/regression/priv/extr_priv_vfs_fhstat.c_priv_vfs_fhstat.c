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
struct stat {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  expect (char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fh ; 
 int fhstat (int /*<<< orphan*/ *,struct stat*) ; 

void
priv_vfs_fhstat(int asroot, int injail, struct test *test)
{
	struct stat sb;
	int error;

	error = fhstat(&fh, &sb);
	if (asroot && injail)
		expect("priv_vfs_fhstat(asroot, injail)", error, -1, EPERM);
	if (asroot && !injail)
		expect("priv_vfs_fhstat(asroot, !injail)", error, 0, 0);
	if (!asroot && injail)
		expect("priv_vfs_fhstat(!asroot, injail)", error, -1, EPERM);
	if (!asroot && !injail)
		expect("priv_vfs_fhstat(!asroot, !injail)", error, -1, EPERM);
}