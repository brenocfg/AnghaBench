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
struct sockaddr_in {scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct in_addr {int s_addr; } ;
struct hostent {char* h_name; int h_length; char** h_addr_list; int /*<<< orphan*/  h_addrtype; int /*<<< orphan*/ * h_aliases; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  addr ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int MAX_ADDRS ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 struct sockaddr_in dns_addr ; 
 int /*<<< orphan*/  dns_req ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  inet_aton (char*,struct in_addr*) ; 
 int ntohl (int) ; 
 int read (int,char*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 char* strstr (char*,char*) ; 
 char* strtok_r (char*,char*,char**) ; 
 scalar_t__ write (int,char*,size_t) ; 

__attribute__((used)) static struct hostent*
roken_gethostby(const char *hostname)
{
    int s;
    struct sockaddr_in addr;
    char *request = NULL;
    char buf[1024];
    int offset = 0;
    int n;
    char *p, *foo;
    size_t len;

    if(dns_addr.sin_family == 0)
	return NULL; /* no configured host */
    addr = dns_addr;
    if (asprintf(&request, "GET %s?%s HTTP/1.0\r\n\r\n", dns_req, hostname) < 0)
	return NULL;
    if(request == NULL)
	return NULL;
    s  = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0) {
	free(request);
	return NULL;
    }
    if(connect(s, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
	close(s);
	free(request);
	return NULL;
    }

    len = strlen(request);
    if(write(s, request, len) != (ssize_t)len) {
	close(s);
	free(request);
	return NULL;
    }
    free(request);
    while(1) {
	n = read(s, buf + offset, sizeof(buf) - offset);
	if(n <= 0)
	    break;
	offset += n;
    }
    buf[offset] = '\0';
    close(s);
    p = strstr(buf, "\r\n\r\n"); /* find end of header */
    if(p) p += 4;
    else return NULL;
    foo = NULL;
    p = strtok_r(p, " \t\r\n", &foo);
    if(p == NULL)
	return NULL;
    {
	/* make a hostent to return */
#define MAX_ADDRS 16
	static struct hostent he;
	static char addrs[4 * MAX_ADDRS];
	static char *addr_list[MAX_ADDRS + 1];
	int num_addrs = 0;

	he.h_name = p;
	he.h_aliases = NULL;
	he.h_addrtype = AF_INET;
	he.h_length = 4;

	while((p = strtok_r(NULL, " \t\r\n", &foo)) && num_addrs < MAX_ADDRS) {
	    struct in_addr ip;
	    inet_aton(p, &ip);
	    ip.s_addr = ntohl(ip.s_addr);
	    addr_list[num_addrs] = &addrs[num_addrs * 4];
	    addrs[num_addrs * 4 + 0] = (ip.s_addr >> 24) & 0xff;
	    addrs[num_addrs * 4 + 1] = (ip.s_addr >> 16) & 0xff;
	    addrs[num_addrs * 4 + 2] = (ip.s_addr >> 8) & 0xff;
	    addrs[num_addrs * 4 + 3] = (ip.s_addr >> 0) & 0xff;
	    addr_list[++num_addrs] = NULL;
	}
	he.h_addr_list = addr_list;
	return &he;
    }
}