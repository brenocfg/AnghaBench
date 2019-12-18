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
typedef  int /*<<< orphan*/  to ;
typedef  scalar_t__ time_t ;
struct tm {int dummy; } ;
struct sshkey_cert {scalar_t__ valid_after; int valid_before; } ;
typedef  int /*<<< orphan*/  ret ;
typedef  int /*<<< orphan*/  from ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 struct tm* localtime (scalar_t__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 size_t strlcpy (char*,char*,size_t) ; 

size_t
sshkey_format_cert_validity(const struct sshkey_cert *cert, char *s, size_t l)
{
	char from[32], to[32], ret[64];
	time_t tt;
	struct tm *tm;

	*from = *to = '\0';
	if (cert->valid_after == 0 &&
	    cert->valid_before == 0xffffffffffffffffULL)
		return strlcpy(s, "forever", l);

	if (cert->valid_after != 0) {
		/* XXX revisit INT_MAX in 2038 :) */
		tt = cert->valid_after > INT_MAX ?
		    INT_MAX : cert->valid_after;
		tm = localtime(&tt);
		strftime(from, sizeof(from), "%Y-%m-%dT%H:%M:%S", tm);
	}
	if (cert->valid_before != 0xffffffffffffffffULL) {
		/* XXX revisit INT_MAX in 2038 :) */
		tt = cert->valid_before > INT_MAX ?
		    INT_MAX : cert->valid_before;
		tm = localtime(&tt);
		strftime(to, sizeof(to), "%Y-%m-%dT%H:%M:%S", tm);
	}

	if (cert->valid_after == 0)
		snprintf(ret, sizeof(ret), "before %s", to);
	else if (cert->valid_before == 0xffffffffffffffffULL)
		snprintf(ret, sizeof(ret), "after %s", from);
	else
		snprintf(ret, sizeof(ret), "from %s to %s", from, to);

	return strlcpy(s, ret, l);
}