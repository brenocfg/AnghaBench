#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  bn; } ;
typedef  TYPE_1__ MINT ;

/* Variables and functions */
 char* BN_bn2hex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 
 int strlen (char*) ; 
 char tolower (char) ; 

__attribute__((used)) static char *
_mtox(const char *msg, const MINT *mp)
{
	char *p, *s, *s2;
	int len;

	s = BN_bn2hex(mp->bn);
	if (s == NULL)
		_bnerr(msg);
	asprintf(&s2, "%s", s);
	if (s2 == NULL)
		MPERR(("%s", msg));
	OPENSSL_free(s);

	/*
	 * This is a kludge for libgmp compatibility.  The latter's
	 * implementation of this function returns lower-case letters,
	 * but BN_bn2hex returns upper-case.  Some programs (e.g.,
	 * newkey(1)) are sensitive to this.  Although it's probably
	 * their fault, it's nice to be compatible.
	 */
	len = strlen(s2);
	for (p = s2; p < s2 + len; p++)
		*p = tolower(*p);

	return (s2);
}