#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ypresp_val {void* stat; } ;
typedef  struct ypresp_val ypresp_val ;
struct TYPE_5__ {int /*<<< orphan*/  keydat_len; int /*<<< orphan*/  keydat_val; } ;
struct TYPE_6__ {char* map; char* domain; TYPE_1__ key; } ;
typedef  TYPE_2__ ypreq_key ;
struct userent {char* ue_line; char* ge_line; char* ue_netid_line; void* ue_uid; void* ge_gid; } ;
struct svc_req {int dummy; } ;
struct groupent {char* ue_line; char* ge_line; char* ue_netid_line; void* ue_uid; void* ge_gid; } ;
struct TYPE_7__ {int /*<<< orphan*/  sc_user_uids; int /*<<< orphan*/ * sc_group_names; int /*<<< orphan*/  sc_group_gids; int /*<<< orphan*/ * sc_user_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_MAX ; 
 struct userent* RB_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct userent*) ; 
 int /*<<< orphan*/  UID_MAX ; 
 int /*<<< orphan*/  YPMAXRECORD ; 
 void* YP_BADARGS ; 
 void* YP_NOKEY ; 
 void* YP_NOMAP ; 
 char* calloc (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* env ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  group_gid_tree ; 
 int /*<<< orphan*/  group_name_tree ; 
 int /*<<< orphan*/  log_debug (char*,...) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strsep (char**,char*) ; 
 void* strtonum (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  user_name_tree ; 
 int /*<<< orphan*/  user_uid_tree ; 
 int /*<<< orphan*/  yp_make_val (struct ypresp_val*,char*,int) ; 
 int yp_valid_domain (char*,struct ypresp_val*) ; 

ypresp_val *
ypproc_match_2_svc(ypreq_key *arg, struct svc_req *req)
{
	struct userent		 ukey;
	struct userent		*ue;
	struct groupent		 gkey;
	struct groupent		*ge;
	static struct ypresp_val res;
	const char		*estr;
	char			*bp, *cp;
	char			 *key;

	log_debug("matching '%.*s' in map %s", arg->key.keydat_len,
	   arg->key.keydat_val, arg->map);

	if (yp_valid_domain(arg->domain, (struct ypresp_val *)&res) == -1)
		return (&res);

	if (env->sc_user_names == NULL) {
		/*
		 * tree not ready.
		 */
		return (NULL);
	}

	if (arg->key.keydat_len > YPMAXRECORD) {
		log_debug("argument too long");
		return (NULL);
	}
	key = calloc(arg->key.keydat_len + 1, 1);
	if (key == NULL)
		return (NULL);
	(void)strncpy(key, arg->key.keydat_val, arg->key.keydat_len);

	if (strcmp(arg->map, "passwd.byname") == 0 ||
	    strcmp(arg->map, "master.passwd.byname") == 0) {
		ukey.ue_line = key;
		if ((ue = RB_FIND(user_name_tree, env->sc_user_names,
		    &ukey)) == NULL) {
			res.stat = YP_NOKEY;
			goto out;
		}

		yp_make_val(&res, ue->ue_line, 1);
		goto out;
	} else if (strcmp(arg->map, "passwd.byuid") == 0 ||
		   strcmp(arg->map, "master.passwd.byuid") == 0) {
		ukey.ue_uid = strtonum(key, 0, UID_MAX, &estr); 
		if (estr) {
			res.stat = YP_BADARGS;
			goto out;
		}

		if ((ue = RB_FIND(user_uid_tree, &env->sc_user_uids,
		    &ukey)) == NULL) {
			res.stat = YP_NOKEY;
			goto out;
		}

		yp_make_val(&res, ue->ue_line, 1);
		return (&res);
	} else if (strcmp(arg->map, "group.bygid") == 0) {
		gkey.ge_gid = strtonum(key, 0, GID_MAX, &estr); 
		if (estr) {
			res.stat = YP_BADARGS;
			goto out;
		}
		if ((ge = RB_FIND(group_gid_tree, &env->sc_group_gids,
		    &gkey)) == NULL) {
			res.stat = YP_NOKEY;
			goto out;
		}

		yp_make_val(&res, ge->ge_line, 1);
		return (&res);
	} else if (strcmp(arg->map, "group.byname") == 0) {
		gkey.ge_line = key;
		if ((ge = RB_FIND(group_name_tree, env->sc_group_names,
		    &gkey)) == NULL) {
			res.stat = YP_NOKEY;
			goto out;
		}

		yp_make_val(&res, ge->ge_line, 1);
		return (&res);
	} else if (strcmp(arg->map, "netid.byname") == 0) {
		bp = cp = key;

		if (strncmp(bp, "unix.", strlen("unix.")) != 0) {
			res.stat = YP_BADARGS;
			goto out;
		}

		bp += strlen("unix.");

		if (*bp == '\0') {
			res.stat = YP_BADARGS;
			goto out;
		}

		if (!(cp = strsep(&bp, "@"))) {
			res.stat = YP_BADARGS;
			goto out;
		}

		if (strcmp(bp, arg->domain) != 0) {
			res.stat = YP_BADARGS;
			goto out;
		}

		ukey.ue_uid = strtonum(cp, 0, UID_MAX, &estr); 
		if (estr) {
			res.stat = YP_BADARGS;
			goto out;
		}

		if ((ue = RB_FIND(user_uid_tree, &env->sc_user_uids,
		    &ukey)) == NULL) {
			res.stat = YP_NOKEY;
			goto out;
		}

		yp_make_val(&res, ue->ue_netid_line, 0);
		goto out;
	
	} else {
		log_debug("unknown map %s", arg->map);
		res.stat = YP_NOMAP;
		goto out;
	}
out:
	free(key);
	return (&res);
}