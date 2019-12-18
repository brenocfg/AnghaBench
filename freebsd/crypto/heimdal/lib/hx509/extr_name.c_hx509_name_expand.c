#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct rk_strpool {int dummy; } ;
typedef  TYPE_6__* hx509_name ;
typedef  int /*<<< orphan*/ * hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_14__ {char* utf8String; } ;
struct TYPE_17__ {scalar_t__ element; TYPE_5__ u; } ;
struct TYPE_12__ {size_t len; TYPE_2__* val; } ;
struct TYPE_13__ {TYPE_3__ rdnSequence; } ;
struct TYPE_16__ {scalar_t__ element; TYPE_4__ u; } ;
struct TYPE_15__ {TYPE_7__ der_name; } ;
struct TYPE_11__ {size_t len; TYPE_1__* val; } ;
struct TYPE_10__ {TYPE_8__ value; } ;
typedef  TYPE_7__ Name ;
typedef  TYPE_8__ DirectoryString ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ choice_DirectoryString_utf8String ; 
 scalar_t__ choice_Name_rdnSequence ; 
 int /*<<< orphan*/  free (char*) ; 
 char* hx509_env_lfind (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 char* rk_strpoolcollect (struct rk_strpool*) ; 
 int /*<<< orphan*/  rk_strpoolfree (struct rk_strpool*) ; 
 struct rk_strpool* rk_strpoolprintf (struct rk_strpool*,char*,...) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 

int
hx509_name_expand(hx509_context context,
		  hx509_name name,
		  hx509_env env)
{
    Name *n = &name->der_name;
    size_t i, j;

    if (env == NULL)
	return 0;

    if (n->element != choice_Name_rdnSequence) {
	hx509_set_error_string(context, 0, EINVAL, "RDN not of supported type");
	return EINVAL;
    }

    for (i = 0 ; i < n->u.rdnSequence.len; i++) {
	for (j = 0; j < n->u.rdnSequence.val[i].len; j++) {
	    /** Only UTF8String rdnSequence names are allowed */
	    /*
	      THIS SHOULD REALLY BE:
	      COMP = n->u.rdnSequence.val[i].val[j];
	      normalize COMP to utf8
	      check if there are variables
	        expand variables
	        convert back to orignal format, store in COMP
	      free normalized utf8 string
	    */
	    DirectoryString *ds = &n->u.rdnSequence.val[i].val[j].value;
	    char *p, *p2;
	    struct rk_strpool *strpool = NULL;

	    if (ds->element != choice_DirectoryString_utf8String) {
		hx509_set_error_string(context, 0, EINVAL, "unsupported type");
		return EINVAL;
	    }
	    p = strstr(ds->u.utf8String, "${");
	    if (p) {
		strpool = rk_strpoolprintf(strpool, "%.*s",
					   (int)(p - ds->u.utf8String),
					   ds->u.utf8String);
		if (strpool == NULL) {
		    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
		    return ENOMEM;
		}
	    }
	    while (p != NULL) {
		/* expand variables */
		const char *value;
		p2 = strchr(p, '}');
		if (p2 == NULL) {
		    hx509_set_error_string(context, 0, EINVAL, "missing }");
		    rk_strpoolfree(strpool);
		    return EINVAL;
		}
		p += 2;
		value = hx509_env_lfind(context, env, p, p2 - p);
		if (value == NULL) {
		    hx509_set_error_string(context, 0, EINVAL,
					   "variable %.*s missing",
					   (int)(p2 - p), p);
		    rk_strpoolfree(strpool);
		    return EINVAL;
		}
		strpool = rk_strpoolprintf(strpool, "%s", value);
		if (strpool == NULL) {
		    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
		    return ENOMEM;
		}
		p2++;

		p = strstr(p2, "${");
		if (p)
		    strpool = rk_strpoolprintf(strpool, "%.*s",
					       (int)(p - p2), p2);
		else
		    strpool = rk_strpoolprintf(strpool, "%s", p2);
		if (strpool == NULL) {
		    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
		    return ENOMEM;
		}
	    }
	    if (strpool) {
		free(ds->u.utf8String);
		ds->u.utf8String = rk_strpoolcollect(strpool);
		if (ds->u.utf8String == NULL) {
		    hx509_set_error_string(context, 0, ENOMEM, "out of memory");
		    return ENOMEM;
		}
	    }
	}
    }
    return 0;
}