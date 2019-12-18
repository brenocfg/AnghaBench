#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ type; } ;
typedef  TYPE_1__ ucl_object_t ;
struct auth_group {int /*<<< orphan*/  ag_name; } ;
struct auth {int dummy; } ;

/* Variables and functions */
 scalar_t__ UCL_STRING ; 
 struct auth* auth_new_chap_mutual (struct auth_group*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_warnx (char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* ucl_object_find_key (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  ucl_object_tostring (TYPE_1__ const*) ; 

__attribute__((used)) static int
uclparse_chap_mutual(struct auth_group *auth_group, const ucl_object_t *obj)
{
	const struct auth *ca;
	const ucl_object_t *user, *secret, *mutual_user;
	const ucl_object_t *mutual_secret;

	user = ucl_object_find_key(obj, "user");
	if (!user || user->type != UCL_STRING) {
		log_warnx("chap-mutual section in auth-group \"%s\" is missing "
		    "\"user\" string key", auth_group->ag_name);
		return (1);
	}

	secret = ucl_object_find_key(obj, "secret");
	if (!secret || secret->type != UCL_STRING) {
		log_warnx("chap-mutual section in auth-group \"%s\" is missing "
		    "\"secret\" string key", auth_group->ag_name);
		return (1);
	}

	mutual_user = ucl_object_find_key(obj, "mutual-user");
	if (!user || user->type != UCL_STRING) {
		log_warnx("chap-mutual section in auth-group \"%s\" is missing "
		    "\"mutual-user\" string key", auth_group->ag_name);
		return (1);
	}	

	mutual_secret = ucl_object_find_key(obj, "mutual-secret");
	if (!secret || secret->type != UCL_STRING) {
		log_warnx("chap-mutual section in auth-group \"%s\" is missing "
		    "\"mutual-secret\" string key", auth_group->ag_name);
		return (1);
	}

	ca = auth_new_chap_mutual(auth_group,
	    ucl_object_tostring(user),
	    ucl_object_tostring(secret),
	    ucl_object_tostring(mutual_user),
	    ucl_object_tostring(mutual_secret));

	if (ca == NULL)
		return (1);

	return (0);
}