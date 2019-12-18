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
struct git_cred {int dummy; } ;
typedef  int /*<<< orphan*/  git_cred_default ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void default_free(struct git_cred *cred)
{
	git_cred_default *c = (git_cred_default *)cred;

	git__free(c);
}