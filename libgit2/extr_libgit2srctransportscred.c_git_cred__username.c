#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char const* username; } ;
typedef  TYPE_1__ git_cred_userpass_plaintext ;
struct TYPE_9__ {char const* username; } ;
typedef  TYPE_2__ git_cred_username ;
struct TYPE_10__ {char const* username; } ;
typedef  TYPE_3__ git_cred_ssh_key ;
struct TYPE_11__ {char const* username; } ;
typedef  TYPE_4__ git_cred_ssh_interactive ;
struct TYPE_12__ {char const* username; } ;
typedef  TYPE_5__ git_cred_ssh_custom ;
struct TYPE_13__ {int credtype; } ;
typedef  TYPE_6__ git_cred ;

/* Variables and functions */
#define  GIT_CREDTYPE_SSH_CUSTOM 133 
#define  GIT_CREDTYPE_SSH_INTERACTIVE 132 
#define  GIT_CREDTYPE_SSH_KEY 131 
#define  GIT_CREDTYPE_SSH_MEMORY 130 
#define  GIT_CREDTYPE_USERNAME 129 
#define  GIT_CREDTYPE_USERPASS_PLAINTEXT 128 

const char *git_cred__username(git_cred *cred)
{
	switch (cred->credtype) {
	case GIT_CREDTYPE_USERNAME:
	{
		git_cred_username *c = (git_cred_username *) cred;
		return c->username;
	}
	case GIT_CREDTYPE_USERPASS_PLAINTEXT:
	{
		git_cred_userpass_plaintext *c = (git_cred_userpass_plaintext *) cred;
		return c->username;
	}
	case GIT_CREDTYPE_SSH_KEY:
	case GIT_CREDTYPE_SSH_MEMORY:
	{
		git_cred_ssh_key *c = (git_cred_ssh_key *) cred;
		return c->username;
	}
	case GIT_CREDTYPE_SSH_CUSTOM:
	{
		git_cred_ssh_custom *c = (git_cred_ssh_custom *) cred;
		return c->username;
	}
	case GIT_CREDTYPE_SSH_INTERACTIVE:
	{
		git_cred_ssh_interactive *c = (git_cred_ssh_interactive *) cred;
		return c->username;
	}

	default:
		return NULL;
	}
}