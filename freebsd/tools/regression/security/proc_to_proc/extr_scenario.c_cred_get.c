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
struct cred {int /*<<< orphan*/  cr_issetugid; int /*<<< orphan*/  cr_svuid; int /*<<< orphan*/  cr_euid; int /*<<< orphan*/  cr_ruid; } ;

/* Variables and functions */
 int getresuid (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issetugid () ; 

__attribute__((used)) static int
cred_get(struct cred *cred)
{
	int error;

	error = getresuid(&cred->cr_ruid, &cred->cr_euid, &cred->cr_svuid);
	if (error)
		return (error);

	cred->cr_issetugid = issetugid();

	return (0);
}