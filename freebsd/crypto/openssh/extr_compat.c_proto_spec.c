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

/* Variables and functions */
 int /*<<< orphan*/  SEP ; 
 int SSH_PROTO_2 ; 
 int SSH_PROTO_UNKNOWN ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  logit (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strsep (char**,int /*<<< orphan*/ ) ; 

int
proto_spec(const char *spec)
{
	char *s, *p, *q;
	int ret = SSH_PROTO_UNKNOWN;

	if (spec == NULL)
		return ret;
	q = s = strdup(spec);
	if (s == NULL)
		return ret;
	for ((p = strsep(&q, SEP)); p && *p != '\0'; (p = strsep(&q, SEP))) {
		switch (atoi(p)) {
		case 2:
			ret |= SSH_PROTO_2;
			break;
		default:
			logit("ignoring bad proto spec: '%s'.", p);
			break;
		}
	}
	free(s);
	return ret;
}