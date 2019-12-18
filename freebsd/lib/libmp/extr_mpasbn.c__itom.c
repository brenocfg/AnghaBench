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
typedef  int /*<<< orphan*/  MINT ;

/* Variables and functions */
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/ * _xtom (char const*,char*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,short) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static MINT *
_itom(const char *msg, short n)
{
	MINT *mp;
	char *s;

	asprintf(&s, "%x", n);
	if (s == NULL)
		MPERR(("%s", msg));
	mp = _xtom(msg, s);
	free(s);
	return (mp);
}