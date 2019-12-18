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
 char* BN_bn2dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPERR (char*) ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 int /*<<< orphan*/  _bnerr (char const*) ; 
 int /*<<< orphan*/  asprintf (char**,char*,char*) ; 

__attribute__((used)) static char *
_mtod(const char *msg, const MINT *mp)
{
	char *s, *s2;

	s = BN_bn2dec(mp->bn);
	if (s == NULL)
		_bnerr(msg);
	asprintf(&s2, "%s", s);
	if (s2 == NULL)
		MPERR(("%s", msg));
	OPENSSL_free(s);
	return (s2);
}