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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int dn_expand (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

const u_char *
p_fqnname(const u_char *cp, const u_char *msg, int msglen, char *name,
    int namelen)
{
	int n, newlen;

	if ((n = dn_expand(msg, cp + msglen, cp, name, namelen)) < 0)
		return (NULL);
	newlen = strlen(name);
	if (newlen == 0 || name[newlen - 1] != '.') {
		if (newlen + 1 >= namelen)	/*%< Lack space for final dot */
			return (NULL);
		else
			strcpy(name + newlen, ".");
	}
	return (cp + n);
}