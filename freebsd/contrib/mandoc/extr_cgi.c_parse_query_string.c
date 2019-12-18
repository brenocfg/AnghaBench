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
struct TYPE_2__ {int equal; int /*<<< orphan*/ * arch; int /*<<< orphan*/ * sec; int /*<<< orphan*/ * manpath; int /*<<< orphan*/ * query; } ;
struct req {int isquery; TYPE_1__ q; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ http_decode (char*) ; 
 char* mandoc_strndup (char const*,size_t) ; 
 int /*<<< orphan*/  set_query_attr (int /*<<< orphan*/ **,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strcspn (char const*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void
parse_query_string(struct req *req, const char *qs)
{
	char		*key, *val;
	size_t		 keysz, valsz;

	req->isquery	= 1;
	req->q.manpath	= NULL;
	req->q.arch	= NULL;
	req->q.sec	= NULL;
	req->q.query	= NULL;
	req->q.equal	= 1;

	key = val = NULL;
	while (*qs != '\0') {

		/* Parse one key. */

		keysz = strcspn(qs, "=;&");
		key = mandoc_strndup(qs, keysz);
		qs += keysz;
		if (*qs != '=')
			goto next;

		/* Parse one value. */

		valsz = strcspn(++qs, ";&");
		val = mandoc_strndup(qs, valsz);
		qs += valsz;

		/* Decode and catch encoding errors. */

		if ( ! (http_decode(key) && http_decode(val)))
			goto next;

		/* Handle key-value pairs. */

		if ( ! strcmp(key, "query"))
			set_query_attr(&req->q.query, &val);

		else if ( ! strcmp(key, "apropos"))
			req->q.equal = !strcmp(val, "0");

		else if ( ! strcmp(key, "manpath")) {
#ifdef COMPAT_OLDURI
			if ( ! strncmp(val, "OpenBSD ", 8)) {
				val[7] = '-';
				if ('C' == val[8])
					val[8] = 'c';
			}
#endif
			set_query_attr(&req->q.manpath, &val);
		}

		else if ( ! (strcmp(key, "sec")
#ifdef COMPAT_OLDURI
		    && strcmp(key, "sektion")
#endif
		    )) {
			if ( ! strcmp(val, "0"))
				*val = '\0';
			set_query_attr(&req->q.sec, &val);
		}

		else if ( ! strcmp(key, "arch")) {
			if ( ! strcmp(val, "default"))
				*val = '\0';
			set_query_attr(&req->q.arch, &val);
		}

		/*
		 * The key must be freed in any case.
		 * The val may have been handed over to the query
		 * structure, in which case it is now NULL.
		 */
next:
		free(key);
		key = NULL;
		free(val);
		val = NULL;

		if (*qs != '\0')
			qs++;
	}
}