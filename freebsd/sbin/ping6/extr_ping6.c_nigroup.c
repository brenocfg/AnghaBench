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
typedef  unsigned char u_int8_t ;
struct in6_addr {int /*<<< orphan*/ * s6_addr; } ;
typedef  int /*<<< orphan*/  hbuf ;
typedef  int /*<<< orphan*/  ctxt ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  MD5Final (unsigned char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,unsigned char*,size_t) ; 
 int NI_MAXHOST ; 
 int /*<<< orphan*/  bcopy (unsigned char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,struct in6_addr*,char*,int) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,struct in6_addr*) ; 
 scalar_t__ isupper (unsigned char) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,size_t) ; 
 char tolower (unsigned char) ; 

__attribute__((used)) static char *
nigroup(char *name, int nig_oldmcprefix)
{
	char *p;
	char *q;
	MD5_CTX ctxt;
	u_int8_t digest[16];
	u_int8_t c;
	size_t l;
	char hbuf[NI_MAXHOST];
	struct in6_addr in6;
	int valid;

	p = strchr(name, '.');
	if (!p)
		p = name + strlen(name);
	l = p - name;
	if (l > 63 || l > sizeof(hbuf) - 1)
		return NULL;	/*label too long*/
	strncpy(hbuf, name, l);
	hbuf[(int)l] = '\0';

	for (q = name; *q; q++) {
		if (isupper(*(unsigned char *)q))
			*q = tolower(*(unsigned char *)q);
	}

	/* generate 16 bytes of pseudo-random value. */
	memset(&ctxt, 0, sizeof(ctxt));
	MD5Init(&ctxt);
	c = l & 0xff;
	MD5Update(&ctxt, &c, sizeof(c));
	MD5Update(&ctxt, (unsigned char *)name, l);
	MD5Final(digest, &ctxt);

	if (nig_oldmcprefix) {
		/* draft-ietf-ipngwg-icmp-name-lookup */
		valid = inet_pton(AF_INET6, "ff02::2:0000:0000", &in6);
	} else {
		/* RFC 4620 */
		valid = inet_pton(AF_INET6, "ff02::2:ff00:0000", &in6);
	}
	if (valid != 1)
		return NULL;	/*XXX*/

	if (nig_oldmcprefix) {
		/* draft-ietf-ipngwg-icmp-name-lookup */
		bcopy(digest, &in6.s6_addr[12], 4);
	} else {
		/* RFC 4620 */
		bcopy(digest, &in6.s6_addr[13], 3);
	}

	if (inet_ntop(AF_INET6, &in6, hbuf, sizeof(hbuf)) == NULL)
		return NULL;

	return strdup(hbuf);
}