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
struct TYPE_3__ {int /*<<< orphan*/  comment; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ Identity ;

/* Variables and functions */
 int /*<<< orphan*/  SSH_FP_DEFAULT ; 
 scalar_t__ ask_permission (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fingerprint_hash ; 
 int /*<<< orphan*/  free (char*) ; 
 char* sshkey_fingerprint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
confirm_key(Identity *id)
{
	char *p;
	int ret = -1;

	p = sshkey_fingerprint(id->key, fingerprint_hash, SSH_FP_DEFAULT);
	if (p != NULL &&
	    ask_permission("Allow use of key %s?\nKey fingerprint %s.",
	    id->comment, p))
		ret = 0;
	free(p);

	return (ret);
}