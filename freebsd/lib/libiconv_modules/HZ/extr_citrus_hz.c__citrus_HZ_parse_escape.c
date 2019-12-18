#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* set; } ;
typedef  TYPE_1__ escape_t ;
typedef  int /*<<< orphan*/  _HZEncodingInfo ;

/* Variables and functions */
 void* E0SET (int /*<<< orphan*/ *) ; 
 void* E1SET (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (void*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int _citrus_prop_parse_variable (int /*<<< orphan*/ ,void*,char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  escape_hints ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
_citrus_HZ_parse_escape(void *context, const char *name, const char *s)
{
	_HZEncodingInfo *ei;
	escape_t *escape;
	void *p[2];

	ei = (_HZEncodingInfo *)context;
	escape = calloc(1, sizeof(*escape));
	if (escape == NULL)
		return (EINVAL);
	if (strcmp("0", name) == 0) {
		escape->set = E0SET(ei);
		TAILQ_INSERT_TAIL(E0SET(ei), escape, entry);
	} else if (strcmp("1", name) == 0) {
		escape->set = E1SET(ei);
		TAILQ_INSERT_TAIL(E1SET(ei), escape, entry);
	} else {
		free(escape);
		return (EINVAL);
	}
	p[0] = (void *)escape;
	p[1] = (void *)ei;
	return (_citrus_prop_parse_variable(
	    escape_hints, (void *)&p[0], s, strlen(s)));
}