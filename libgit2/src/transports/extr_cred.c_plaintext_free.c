#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct git_cred {int dummy; } ;
struct TYPE_5__ {struct TYPE_5__* password; struct TYPE_5__* username; } ;
typedef  TYPE_1__ git_cred_userpass_plaintext ;

/* Variables and functions */
 int /*<<< orphan*/  git__free (TYPE_1__*) ; 
 int /*<<< orphan*/  git__memzero (TYPE_1__*,size_t) ; 
 size_t strlen (TYPE_1__*) ; 

__attribute__((used)) static void plaintext_free(struct git_cred *cred)
{
	git_cred_userpass_plaintext *c = (git_cred_userpass_plaintext *)cred;

	git__free(c->username);

	/* Zero the memory which previously held the password */
	if (c->password) {
		size_t pass_len = strlen(c->password);
		git__memzero(c->password, pass_len);
		git__free(c->password);
	}

	git__free(c);
}