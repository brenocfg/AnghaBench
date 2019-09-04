#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* email; struct TYPE_4__* name; } ;
typedef  TYPE_1__ git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 

void git_signature_free(git_signature *sig)
{
	if (sig == NULL)
		return;

	git__free(sig->name);
	sig->name = NULL;
	git__free(sig->email);
	sig->email = NULL;
	git__free(sig);
}