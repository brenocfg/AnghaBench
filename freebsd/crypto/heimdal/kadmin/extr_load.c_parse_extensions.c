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
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int len; int /*<<< orphan*/ * val; } ;
typedef  TYPE_1__ HDB_extensions ;
typedef  int /*<<< orphan*/  HDB_extension ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 TYPE_1__* calloc (int,int) ; 
 int decode_HDB_extension (void*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ hex_decode (char*,void*,scalar_t__) ; 
 void* malloc (scalar_t__) ; 
 void* realloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 char* strsep (char**,char*) ; 

__attribute__((used)) static int
parse_extensions(char *str, HDB_extensions **e)
{
    char *p;
    int ret;

    if(strcmp(str, "-") == 0 || *str == '\0') {
	*e = NULL;
	return 0;
    }
    *e = calloc(1, sizeof(**e));

    p = strsep(&str, ":");

    while (p) {
	HDB_extension ext;
	ssize_t len;
	void *d;

	len = strlen(p);
	d = malloc(len);

	len = hex_decode(p, d, len);
	if (len < 0) {
	    free(d);
	    return -1;
	}

	ret = decode_HDB_extension(d, len, &ext, NULL);
	free(d);
	if (ret)
	    return -1;
	d = realloc((*e)->val, ((*e)->len + 1) * sizeof((*e)->val[0]));
	if (d == NULL)
	    abort();
	(*e)->val = d;
	(*e)->val[(*e)->len] = ext;
	(*e)->len++;

	p = strsep(&str, ":");
    }

    return 0;
}