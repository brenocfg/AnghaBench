#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int lt_start; int lt_end; int /*<<< orphan*/  lt_dow; } ;
typedef  TYPE_1__ login_time_t ;
struct TYPE_6__ {int /*<<< orphan*/  cn; int /*<<< orphan*/  fl; int /*<<< orphan*/ * dw; } ;

/* Variables and functions */
 int /*<<< orphan*/  LTM_ANY ; 
 int /*<<< orphan*/  LTM_NONE ; 
 TYPE_4__* dws ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 char* parse_time (char*,int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ tolower (char) ; 

login_time_t
parse_lt(const char *str)
{
    login_time_t    t;

    memset(&t, 0, sizeof t);
    t.lt_dow = LTM_NONE;
    if (str && *str && strcmp(str, "Never") != 0 && strcmp(str, "None") != 0) {
	int		 i;
	login_time_t	 m = t;
	char		*p;
	char		 buf[64];

	/* Make local copy and force lowercase to simplify parsing */
	strlcpy(buf, str, sizeof buf);
	for (i = 0; buf[i]; i++)
	    buf[i] = (char)tolower(buf[i]);
	p = buf;

	while (isalpha(*p)) {

	    i = 0;
	    while (dws[i].dw && strncmp(p, dws[i].dw, dws[i].cn) != 0)
		i++;
	    if (dws[i].dw == NULL)
		break;
	    m.lt_dow |= dws[i].fl;
	    p += dws[i].cn;
	}

	if (m.lt_dow == LTM_NONE) /* No (valid) prefix, assume any */
	    m.lt_dow |= LTM_ANY;

	if (isdigit(*p))
	    p = parse_time(p, &m.lt_start);
	else
	    m.lt_start = 0;
	if (*p == '-')
	    p = parse_time(p + 1, &m.lt_end);
	else
	    m.lt_end = 1440;

	t = m;
    }
    return (t);
}