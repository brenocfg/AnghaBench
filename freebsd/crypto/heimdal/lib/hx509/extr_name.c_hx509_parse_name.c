#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_name ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  heim_oid ;
struct TYPE_7__ {int /*<<< orphan*/  element; } ;
struct TYPE_6__ {TYPE_5__ der_name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int HX509_NAME_MALFORMED ; 
 int HX509_PARSING_NAME_FAILED ; 
 int _hx509_name_modify (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  choice_Name_rdnSequence ; 
 int /*<<< orphan*/  der_free_oid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_name_free (TYPE_1__**) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int stringtooid (char const*,int,int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 

int
hx509_parse_name(hx509_context context, const char *str, hx509_name *name)
{
    const char *p, *q;
    size_t len;
    hx509_name n;
    int ret;

    *name = NULL;

    n = calloc(1, sizeof(*n));
    if (n == NULL) {
	hx509_set_error_string(context, 0, ENOMEM, "out of memory");
	return ENOMEM;
    }

    n->der_name.element = choice_Name_rdnSequence;

    p = str;

    while (p != NULL && *p != '\0') {
	heim_oid oid;
	int last;

	q = strchr(p, ',');
	if (q) {
	    len = (q - p);
	    last = 1;
	} else {
	    len = strlen(p);
	    last = 0;
	}

	q = strchr(p, '=');
	if (q == NULL) {
	    ret = HX509_PARSING_NAME_FAILED;
	    hx509_set_error_string(context, 0, ret, "missing = in %s", p);
	    goto out;
	}
	if (q == p) {
	    ret = HX509_PARSING_NAME_FAILED;
	    hx509_set_error_string(context, 0, ret,
				   "missing name before = in %s", p);
	    goto out;
	}

	if ((size_t)(q - p) > len) {
	    ret = HX509_PARSING_NAME_FAILED;
	    hx509_set_error_string(context, 0, ret, " = after , in %s", p);
	    goto out;
	}

	ret = stringtooid(p, q - p, &oid);
	if (ret) {
	    ret = HX509_PARSING_NAME_FAILED;
	    hx509_set_error_string(context, 0, ret,
				   "unknown type: %.*s", (int)(q - p), p);
	    goto out;
	}

	{
	    size_t pstr_len = len - (q - p) - 1;
	    const char *pstr = p + (q - p) + 1;
	    char *r;

	    r = malloc(pstr_len + 1);
	    if (r == NULL) {
		der_free_oid(&oid);
		ret = ENOMEM;
		hx509_set_error_string(context, 0, ret, "out of memory");
		goto out;
	    }
	    memcpy(r, pstr, pstr_len);
	    r[pstr_len] = '\0';

	    ret = _hx509_name_modify(context, &n->der_name, 0, &oid, r);
	    free(r);
	    der_free_oid(&oid);
	    if(ret)
		goto out;
	}
	p += len + last;
    }

    *name = n;

    return 0;
out:
    hx509_name_free(&n);
    return HX509_NAME_MALFORMED;
}