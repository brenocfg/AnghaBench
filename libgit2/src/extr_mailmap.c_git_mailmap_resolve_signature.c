#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  sign; int /*<<< orphan*/  offset; int /*<<< orphan*/  time; } ;
struct TYPE_7__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;
typedef  int /*<<< orphan*/  git_mailmap ;

/* Variables and functions */
 int git_mailmap_resolve (char const**,char const**,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int git_signature_new (TYPE_2__**,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int git_mailmap_resolve_signature(
	git_signature **out, const git_mailmap *mailmap, const git_signature *sig)
{
	const char *name = NULL;
	const char *email = NULL;
	int error;

	if (!sig)
		return 0;

	error = git_mailmap_resolve(&name, &email, mailmap, sig->name, sig->email);
	if (error < 0)
		return error;

	error = git_signature_new(out, name, email, sig->when.time, sig->when.offset);
	if (error < 0)
		return error;

	/* Copy over the sign, as git_signature_new doesn't let you pass it. */
	(*out)->when.sign = sig->when.sign;
	return 0;
}