#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
struct TYPE_3__ {scalar_t__ ident_email; scalar_t__ ident_name; } ;
typedef  TYPE_1__ git_repository ;

/* Variables and functions */
 int git_signature_now (int /*<<< orphan*/ **,scalar_t__,scalar_t__) ; 

int configured_ident(git_signature **out, const git_repository *repo)
{
	if (repo->ident_name && repo->ident_email)
		return git_signature_now(out, repo->ident_name, repo->ident_email);

	/* if not configured let us fall-through to the next method  */
	return -1;
}