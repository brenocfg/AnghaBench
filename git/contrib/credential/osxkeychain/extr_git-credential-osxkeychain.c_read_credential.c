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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  die (char*,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ ) ; 
 void* host ; 
 int /*<<< orphan*/  kSecProtocolTypeFTP ; 
 int /*<<< orphan*/  kSecProtocolTypeFTPS ; 
 int /*<<< orphan*/  kSecProtocolTypeHTTP ; 
 int /*<<< orphan*/  kSecProtocolTypeHTTPS ; 
 int /*<<< orphan*/  kSecProtocolTypeIMAP ; 
 int /*<<< orphan*/  kSecProtocolTypeIMAPS ; 
 int /*<<< orphan*/  kSecProtocolTypeSMTP ; 
 void* password ; 
 void* path ; 
 int /*<<< orphan*/  port ; 
 int /*<<< orphan*/  protocol ; 
 int /*<<< orphan*/  stdin ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int strlen (char*) ; 
 void* username ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static void read_credential(void)
{
	char buf[1024];

	while (fgets(buf, sizeof(buf), stdin)) {
		char *v;

		if (!strcmp(buf, "\n"))
			break;
		buf[strlen(buf)-1] = '\0';

		v = strchr(buf, '=');
		if (!v)
			die("bad input: %s", buf);
		*v++ = '\0';

		if (!strcmp(buf, "protocol")) {
			if (!strcmp(v, "imap"))
				protocol = kSecProtocolTypeIMAP;
			else if (!strcmp(v, "imaps"))
				protocol = kSecProtocolTypeIMAPS;
			else if (!strcmp(v, "ftp"))
				protocol = kSecProtocolTypeFTP;
			else if (!strcmp(v, "ftps"))
				protocol = kSecProtocolTypeFTPS;
			else if (!strcmp(v, "https"))
				protocol = kSecProtocolTypeHTTPS;
			else if (!strcmp(v, "http"))
				protocol = kSecProtocolTypeHTTP;
			else if (!strcmp(v, "smtp"))
				protocol = kSecProtocolTypeSMTP;
			else /* we don't yet handle other protocols */
				exit(0);
		}
		else if (!strcmp(buf, "host")) {
			char *colon = strchr(v, ':');
			if (colon) {
				*colon++ = '\0';
				port = atoi(colon);
			}
			host = xstrdup(v);
		}
		else if (!strcmp(buf, "path"))
			path = xstrdup(v);
		else if (!strcmp(buf, "username"))
			username = xstrdup(v);
		else if (!strcmp(buf, "password"))
			password = xstrdup(v);
	}
}