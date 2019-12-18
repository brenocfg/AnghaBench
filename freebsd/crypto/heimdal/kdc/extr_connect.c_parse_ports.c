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
typedef  int /*<<< orphan*/  krb5_kdc_configuration ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  add_port_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  add_standard_ports (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char*,char**) ; 

__attribute__((used)) static void
parse_ports(krb5_context context,
	    krb5_kdc_configuration *config,
	    const char *str)
{
    char *pos = NULL;
    char *p;
    char *str_copy = strdup (str);

    p = strtok_r(str_copy, " \t", &pos);
    while(p != NULL) {
	if(strcmp(p, "+") == 0) {
#ifdef HAVE_IPV6
	    add_standard_ports(context, config, AF_INET6);
#endif
	    add_standard_ports(context, config, AF_INET);
	} else {
	    char *q = strchr(p, '/');
	    if(q){
		*q++ = 0;
#ifdef HAVE_IPV6
		add_port_string(context, AF_INET6, p, q);
#endif
		add_port_string(context, AF_INET, p, q);
	    }else {
#ifdef HAVE_IPV6
		add_port_string(context, AF_INET6, p, "udp");
		add_port_string(context, AF_INET6, p, "tcp");
#endif
		add_port_string(context, AF_INET, p, "udp");
		add_port_string(context, AF_INET, p, "tcp");
	    }
	}

	p = strtok_r(NULL, " \t", &pos);
    }
    free (str_copy);
}