#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct auth_group {scalar_t__ ag_type; TYPE_1__* ag_target; int /*<<< orphan*/ * ag_name; } ;
typedef  struct auth {void* a_mutual_secret; void* a_mutual_user; void* a_secret; void* a_user; } const auth ;
struct TYPE_2__ {int /*<<< orphan*/ * t_name; } ;

/* Variables and functions */
 scalar_t__ AG_TYPE_CHAP_MUTUAL ; 
 scalar_t__ AG_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  auth_check_secret_length (struct auth const*) ; 
 struct auth const* auth_new (struct auth_group*) ; 
 void* checked_strdup (char const*) ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ *) ; 

const struct auth *
auth_new_chap_mutual(struct auth_group *ag, const char *user,
    const char *secret, const char *user2, const char *secret2)
{
	struct auth *auth;

	if (ag->ag_type == AG_TYPE_UNKNOWN)
		ag->ag_type = AG_TYPE_CHAP_MUTUAL;
	if (ag->ag_type != AG_TYPE_CHAP_MUTUAL) {
		if (ag->ag_name != NULL)
			log_warnx("cannot mix \"chap-mutual\" authentication "
			    "with other types for auth-group \"%s\"",
			    ag->ag_name);
		else
			log_warnx("cannot mix \"chap-mutual\" authentication "
			    "with other types for target \"%s\"",
			    ag->ag_target->t_name);
		return (NULL);
	}

	auth = auth_new(ag);
	auth->a_user = checked_strdup(user);
	auth->a_secret = checked_strdup(secret);
	auth->a_mutual_user = checked_strdup(user2);
	auth->a_mutual_secret = checked_strdup(secret2);

	auth_check_secret_length(auth);

	return (auth);
}