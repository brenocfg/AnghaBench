#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct fileptr {int dummy; } ;
typedef  int /*<<< orphan*/  krb5_error_code ;
struct TYPE_6__ {int /*<<< orphan*/  list; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ krb5_config_section ;
typedef  int /*<<< orphan*/  krb5_config_binding ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int KRB5_BUFSIZ ; 
 int /*<<< orphan*/ * config_fgets (char*,int,struct fileptr*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  parse_binding (struct fileptr*,unsigned int*,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  parse_section (char*,TYPE_2__**,TYPE_2__**,char const**) ; 
 size_t strcspn (char*,char*) ; 

__attribute__((used)) static krb5_error_code
krb5_config_parse_debug (struct fileptr *f,
			 krb5_config_section **res,
			 unsigned *lineno,
			 const char **err_message)
{
    krb5_config_section *s = NULL;
    krb5_config_binding *b = NULL;
    char buf[KRB5_BUFSIZ];
    krb5_error_code ret;

    while (config_fgets(buf, sizeof(buf), f) != NULL) {
	char *p;

	++*lineno;
	buf[strcspn(buf, "\r\n")] = '\0';
	p = buf;
	while(isspace((unsigned char)*p))
	    ++p;
	if (*p == '#' || *p == ';')
	    continue;
	if (*p == '[') {
	    ret = parse_section(p, &s, res, err_message);
	    if (ret)
		return ret;
	    b = NULL;
	} else if (*p == '}') {
	    *err_message = "unmatched }";
	    return EINVAL;	/* XXX */
	} else if(*p != '\0') {
	    if (s == NULL) {
		*err_message = "binding before section";
		return EINVAL;
	    }
	    ret = parse_binding(f, lineno, p, &b, &s->u.list, err_message);
	    if (ret)
		return ret;
	}
    }
    return 0;
}