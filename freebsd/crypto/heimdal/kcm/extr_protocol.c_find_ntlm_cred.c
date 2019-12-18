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
struct kcm_ntlm_cred {int /*<<< orphan*/  session; int /*<<< orphan*/  uid; int /*<<< orphan*/  domain; int /*<<< orphan*/  user; struct kcm_ntlm_cred* next; } ;
typedef  int /*<<< orphan*/  kcm_client ;

/* Variables and functions */
 scalar_t__ kcm_is_same_session (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kcm_ntlm_cred* ntlm_head ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kcm_ntlm_cred *
find_ntlm_cred(const char *user, const char *domain, kcm_client *client)
{
    struct kcm_ntlm_cred *c;

    for (c = ntlm_head; c != NULL; c = c->next)
	if ((user[0] == '\0' || strcmp(user, c->user) == 0) &&
	    (domain == NULL || strcmp(domain, c->domain) == 0) &&
	    kcm_is_same_session(client, c->uid, c->session))
	    return c;

    return NULL;
}