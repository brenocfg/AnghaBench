#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_3__ {char* pw_name; } ;

/* Variables and functions */
 int NBBY ; 
 size_t TYPE_A ; 
 size_t TYPE_E ; 
 size_t TYPE_L ; 
 int UC (int /*<<< orphan*/ ) ; 
 scalar_t__ askpasswd ; 
 int bytesize ; 
 int data ; 
 struct sockaddr_in data_dest ; 
 size_t form ; 
 char** formnames ; 
 scalar_t__ guest ; 
 TYPE_2__ his_addr ; 
 int /*<<< orphan*/  hostname ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 scalar_t__ logged_in ; 
 int /*<<< orphan*/  lreply (int,char*,int /*<<< orphan*/ ,char*) ; 
 size_t mode ; 
 char** modenames ; 
 struct sockaddr_in pasv_addr ; 
 int pdata ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 TYPE_1__* pw ; 
 char* remotehost ; 
 int /*<<< orphan*/  reply (int,char*) ; 
 size_t stru ; 
 char** strunames ; 
 size_t type ; 
 char** typenames ; 
 scalar_t__ usedefault ; 
 char* version ; 

void
statcmd(void)
{
#if 0
	struct sockaddr_in *sin;
	u_char *a, *p;

	lreply(211, "%s FTP server (%s) status:", hostname, version);
	printf("     %s\r\n", version);
	printf("     Connected to %s", remotehost);
	if (!isdigit((unsigned char)remotehost[0]))
		printf(" (%s)", inet_ntoa(his_addr.sin_addr));
	printf("\r\n");
	if (logged_in) {
		if (guest)
			printf("     Logged in anonymously\r\n");
		else
			printf("     Logged in as %s\r\n", pw->pw_name);
	} else if (askpasswd)
		printf("     Waiting for password\r\n");
	else
		printf("     Waiting for user name\r\n");
	printf("     TYPE: %s", typenames[type]);
	if (type == TYPE_A || type == TYPE_E)
		printf(", FORM: %s", formnames[form]);
	if (type == TYPE_L)
#if NBBY == 8
		printf(" %d", NBBY);
#else
		printf(" %d", bytesize);	/* need definition! */
#endif
	printf("; STRUcture: %s; transfer MODE: %s\r\n",
	    strunames[stru], modenames[mode]);
	if (data != -1)
		printf("     Data connection open\r\n");
	else if (pdata != -1) {
		printf("     in Passive mode");
		sin = &pasv_addr;
		goto printaddr;
	} else if (usedefault == 0) {
		printf("     PORT");
		sin = &data_dest;
printaddr:
		a = (u_char *) &sin->sin_addr;
		p = (u_char *) &sin->sin_port;
#define UC(b) (((int) b) & 0xff)
		printf(" (%d,%d,%d,%d,%d,%d)\r\n", UC(a[0]),
			UC(a[1]), UC(a[2]), UC(a[3]), UC(p[0]), UC(p[1]));
#undef UC
	} else
		printf("     No data connection\r\n");
#endif
	reply(211, "End of status");
}