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
 int HEXKEYBYTES ; 
 int /*<<< orphan*/  KEYCHECKSUMSIZE ; 
 int /*<<< orphan*/  getpublicandprivatekey (char*,char*) ; 
 scalar_t__ memcmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xdecrypt (char*,char*) ; 

int
getsecretkey(char *netname, char *secretkey, char *passwd)
{
	char lookup[3 * HEXKEYBYTES];
	char *p;

	if (secretkey == NULL)
		return (0);
	if (!getpublicandprivatekey(netname, lookup))
		return (0);
	p = strchr(lookup, ':');
	if (p == NULL) {
		return (0);
	}
	p++;
	if (!xdecrypt(p, passwd)) {
		return (0);
	}
	if (memcmp(p, p + HEXKEYBYTES, KEYCHECKSUMSIZE) != 0) {
		secretkey[0] = '\0';
		return (1);
	}
	p[HEXKEYBYTES] = '\0';
	(void) strncpy(secretkey, p, HEXKEYBYTES);
	secretkey[HEXKEYBYTES] = '\0';
	return (1);
}