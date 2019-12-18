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
 size_t strspn (char*,char*) ; 

__attribute__((used)) static void
parsemsg_rfc3164_app_name_procid(char **msg, const char **app_name,
    const char **procid) {
	char *m, *app_name_begin, *procid_begin;
	size_t app_name_length, procid_length;

	m = *msg;

	/* Application name. */
	app_name_begin = m;
	app_name_length = strspn(m,
	    "abcdefghijklmnopqrstuvwxyz"
	    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	    "0123456789"
	    "_-/");
	if (app_name_length == 0)
		goto bad;
	m += app_name_length;

	/* Process identifier (optional). */
	if (*m == '[') {
		procid_begin = ++m;
		procid_length = strspn(m, "0123456789");
		if (procid_length == 0)
			goto bad;
		m += procid_length;
		if (*m++ != ']')
			goto bad;
	} else {
		procid_begin = NULL;
		procid_length = 0;
	}

	/* Separator. */
	if (m[0] != ':' || m[1] != ' ')
		goto bad;

	/* Split strings from input. */
	app_name_begin[app_name_length] = '\0';
	if (procid_begin != 0)
		procid_begin[procid_length] = '\0';

	*msg = m + 2;
	*app_name = app_name_begin;
	*procid = procid_begin;
	return;
bad:
	*app_name = NULL;
	*procid = NULL;
}