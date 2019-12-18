#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int length; unsigned int* components; } ;
typedef  TYPE_1__ heim_oid ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 long INT_MAX ; 
 int /*<<< orphan*/  der_free_oid (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 unsigned int* realloc (unsigned int*,int) ; 
 char* strdup (char const*) ; 
 char* strtok_r (char*,char const*,char**) ; 
 long strtol (char*,char**,int) ; 

int
der_parse_heim_oid (const char *str, const char *sep, heim_oid *data)
{
    char *s, *w, *brkt, *endptr;
    unsigned int *c;
    long l;

    data->length = 0;
    data->components = NULL;

    if (sep == NULL)
	sep = ".";

    s = strdup(str);

    for (w = strtok_r(s, sep, &brkt);
	 w != NULL;
	 w = strtok_r(NULL, sep, &brkt)) {

	c = realloc(data->components,
		    (data->length + 1) * sizeof(data->components[0]));
	if (c == NULL) {
	    der_free_oid(data);
	    free(s);
	    return ENOMEM;
	}
	data->components = c;

	l = strtol(w, &endptr, 10);
	if (*endptr != '\0' || l < 0 || l > INT_MAX) {
	    der_free_oid(data);
	    free(s);
	    return EINVAL;
	}
	data->components[data->length++] = l;
    }
    free(s);
    return 0;
}