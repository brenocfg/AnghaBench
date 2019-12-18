#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  free; int /*<<< orphan*/  credtype; } ;
struct TYPE_9__ {size_t publickey_len; TYPE_2__ parent; void* payload; int /*<<< orphan*/  sign_callback; struct TYPE_9__* publickey; struct TYPE_9__* username; } ;
typedef  TYPE_1__ git_cred_ssh_custom ;
typedef  int /*<<< orphan*/  git_cred_sign_cb ;
typedef  TYPE_2__ git_cred ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CREDTYPE_SSH_CUSTOM ; 
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* git__calloc (int,int) ; 
 TYPE_1__* git__malloc (size_t) ; 
 TYPE_1__* git__strdup (char const*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,char const*,size_t) ; 
 int /*<<< orphan*/  ssh_custom_free ; 

int git_cred_ssh_custom_new(
	git_cred **cred,
	const char *username,
	const char *publickey,
	size_t publickey_len,
	git_cred_sign_cb sign_callback,
	void *payload)
{
	git_cred_ssh_custom *c;

	assert(username && cred);

	c = git__calloc(1, sizeof(git_cred_ssh_custom));
	GIT_ERROR_CHECK_ALLOC(c);

	c->parent.credtype = GIT_CREDTYPE_SSH_CUSTOM;
	c->parent.free = ssh_custom_free;

	c->username = git__strdup(username);
	GIT_ERROR_CHECK_ALLOC(c->username);

	if (publickey_len > 0) {
		c->publickey = git__malloc(publickey_len);
		GIT_ERROR_CHECK_ALLOC(c->publickey);

		memcpy(c->publickey, publickey, publickey_len);
	}

	c->publickey_len = publickey_len;
	c->sign_callback = sign_callback;
	c->payload = payload;

	*cred = &c->parent;
	return 0;
}