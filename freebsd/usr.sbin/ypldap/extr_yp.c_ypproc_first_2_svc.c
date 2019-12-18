#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ypresp_key_val {int /*<<< orphan*/  stat; } ;
typedef  struct ypresp_key_val ypresp_key_val ;
struct TYPE_4__ {int /*<<< orphan*/  map; int /*<<< orphan*/  domain; } ;
typedef  TYPE_1__ ypreq_nokey ;
struct ypresp_val {int dummy; } ;
struct svc_req {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * sc_group_lines; int /*<<< orphan*/ * sc_user_lines; } ;

/* Variables and functions */
 int /*<<< orphan*/  YP_NOMAP ; 
 TYPE_3__* env ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  yp_make_keyval (struct ypresp_key_val*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int yp_valid_domain (int /*<<< orphan*/ ,struct ypresp_val*) ; 

ypresp_key_val *
ypproc_first_2_svc(ypreq_nokey *arg, struct svc_req *req)
{
	static struct ypresp_key_val	res;

	if (yp_valid_domain(arg->domain, (struct ypresp_val *)&res) == -1)
		return (&res);

	if (strcmp(arg->map, "passwd.byname") == 0 ||
	    strcmp(arg->map, "master.passwd.byname") == 0) {
		if (env->sc_user_lines == NULL)
			return (NULL);

		yp_make_keyval(&res, env->sc_user_lines, env->sc_user_lines);
	} else if (strcmp(arg->map, "group.byname") == 0) {
		if (env->sc_group_lines == NULL)
			return (NULL);

		yp_make_keyval(&res, env->sc_group_lines, env->sc_group_lines);
	} else {
		log_debug("unknown map %s", arg->map);
		res.stat = YP_NOMAP;
	}

	return (&res);
}