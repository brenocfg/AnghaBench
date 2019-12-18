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
struct stat {size_t ss_len; } ;
struct sockaddr_storage {size_t ss_len; } ;
struct sockaddr {int dummy; } ;
struct itimerval {size_t ss_len; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  struct stat cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  isalpha (char) ; 
 int /*<<< orphan*/  ktrcaprights (struct stat*) ; 
 int /*<<< orphan*/  ktritimerval (struct stat*) ; 
 int /*<<< orphan*/  ktrsockaddr (struct sockaddr*) ; 
 int /*<<< orphan*/  ktrstat (struct stat*) ; 
 int /*<<< orphan*/  memcpy (struct stat*,char*,size_t) ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

void
ktrstruct(char *buf, size_t buflen)
{
	char *name, *data;
	size_t namelen, datalen;
	int i;
	cap_rights_t rights;
	struct itimerval it;
	struct stat sb;
	struct sockaddr_storage ss;

	for (name = buf, namelen = 0;
	     namelen < buflen && name[namelen] != '\0';
	     ++namelen)
		/* nothing */;
	if (namelen == buflen)
		goto invalid;
	if (name[namelen] != '\0')
		goto invalid;
	data = buf + namelen + 1;
	datalen = buflen - namelen - 1;
	if (datalen == 0)
		goto invalid;
	/* sanity check */
	for (i = 0; i < (int)namelen; ++i)
		if (!isalpha(name[i]))
			goto invalid;
	if (strcmp(name, "caprights") == 0) {
		if (datalen != sizeof(cap_rights_t))
			goto invalid;
		memcpy(&rights, data, datalen);
		ktrcaprights(&rights);
	} else if (strcmp(name, "itimerval") == 0) {
		if (datalen != sizeof(struct itimerval))
			goto invalid;
		memcpy(&it, data, datalen);
		ktritimerval(&it);
	} else if (strcmp(name, "stat") == 0) {
		if (datalen != sizeof(struct stat))
			goto invalid;
		memcpy(&sb, data, datalen);
		ktrstat(&sb);
	} else if (strcmp(name, "sockaddr") == 0) {
		if (datalen > sizeof(ss))
			goto invalid;
		memcpy(&ss, data, datalen);
		if (datalen != ss.ss_len)
			goto invalid;
		ktrsockaddr((struct sockaddr *)&ss);
	} else {
		printf("unknown structure\n");
	}
	return;
invalid:
	printf("invalid record\n");
}