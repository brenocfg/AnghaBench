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
struct addrinfo {void* ai_socktype; int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_canonname; scalar_t__ ai_addrlen; scalar_t__ ai_protocol; int /*<<< orphan*/  ai_family; scalar_t__ ai_flags; } ;
typedef  int /*<<< orphan*/  service ;
typedef  int /*<<< orphan*/  krb5_context ;
typedef  int /*<<< orphan*/  hostname ;

/* Variables and functions */
 int EAI_SERVICE ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 void* SOCK_DGRAM ; 
 void* SOCK_STREAM ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  isdigit (unsigned char) ; 
 int /*<<< orphan*/  krb5_warnx (int /*<<< orphan*/ ,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 size_t strcspn (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ strsep_copy (char const**,char*,char*,int) ; 
 int strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_host(krb5_context context, const char *path, char *data)
{
    int ret;
    char hostname[128];
    const char *p = data;
    struct addrinfo hints;
    char service[32];
    int defport;
    struct addrinfo *ai;

    hints.ai_flags = 0;
    hints.ai_family = PF_UNSPEC;
    hints.ai_socktype = 0;
    hints.ai_protocol = 0;

    hints.ai_addrlen = 0;
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;
    hints.ai_next = NULL;

    /* XXX data could be a list of hosts that this code can't handle */
    /* XXX copied from krbhst.c */
    if(strncmp(p, "http://", 7) == 0){
        p += 7;
	hints.ai_socktype = SOCK_STREAM;
	strlcpy(service, "http", sizeof(service));
	defport = 80;
    } else if(strncmp(p, "http/", 5) == 0) {
        p += 5;
	hints.ai_socktype = SOCK_STREAM;
	strlcpy(service, "http", sizeof(service));
	defport = 80;
    }else if(strncmp(p, "tcp/", 4) == 0){
        p += 4;
	hints.ai_socktype = SOCK_STREAM;
	strlcpy(service, "kerberos", sizeof(service));
	defport = 88;
    } else if(strncmp(p, "udp/", 4) == 0) {
        p += 4;
	hints.ai_socktype = SOCK_DGRAM;
	strlcpy(service, "kerberos", sizeof(service));
	defport = 88;
    } else {
	hints.ai_socktype = SOCK_DGRAM;
	strlcpy(service, "kerberos", sizeof(service));
	defport = 88;
    }
    if(strsep_copy(&p, ":", hostname, sizeof(hostname)) < 0) {
	return 1;
    }
    hostname[strcspn(hostname, "/")] = '\0';
    if(p != NULL) {
	char *end;
	int tmp = strtol(p, &end, 0);
	if(end == p) {
	    krb5_warnx(context, "%s: failed to parse port number in %s",
		       path, data);
	    return 1;
	}
	defport = tmp;
	snprintf(service, sizeof(service), "%u", defport);
    }
    ret = getaddrinfo(hostname, service, &hints, &ai);
    if(ret == EAI_SERVICE && !isdigit((unsigned char)service[0])) {
	snprintf(service, sizeof(service), "%u", defport);
	ret = getaddrinfo(hostname, service, &hints, &ai);
    }
    if(ret != 0) {
	krb5_warnx(context, "%s: %s (%s)", path, gai_strerror(ret), hostname);
	return 1;
    }
    return 0;
}