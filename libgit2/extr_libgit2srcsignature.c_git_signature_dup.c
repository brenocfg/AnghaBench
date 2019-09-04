#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  sign; int /*<<< orphan*/  offset; int /*<<< orphan*/  time; } ;
struct TYPE_9__ {TYPE_1__ when; struct TYPE_9__* email; struct TYPE_9__* name; } ;
typedef  TYPE_2__ git_signature ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_2__*) ; 
 TYPE_2__* git__calloc (int,int) ; 
 void* git__strdup (TYPE_2__*) ; 

int git_signature_dup(git_signature **dest, const git_signature *source)
{
	git_signature *signature;

	if (source == NULL)
		return 0;

	signature = git__calloc(1, sizeof(git_signature));
	GIT_ERROR_CHECK_ALLOC(signature);

	signature->name = git__strdup(source->name);
	GIT_ERROR_CHECK_ALLOC(signature->name);

	signature->email = git__strdup(source->email);
	GIT_ERROR_CHECK_ALLOC(signature->email);

	signature->when.time = source->when.time;
	signature->when.offset = source->when.offset;
	signature->when.sign = source->when.sign;

	*dest = signature;

	return 0;
}