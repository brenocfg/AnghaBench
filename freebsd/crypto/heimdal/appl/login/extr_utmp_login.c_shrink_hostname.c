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
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; } ;
typedef  int /*<<< orphan*/  local_hostname ;

/* Variables and functions */
 int MaxHostNameLen ; 
 int /*<<< orphan*/  NI_NUMERICHOST ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int getaddrinfo (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct addrinfo**) ; 
 int /*<<< orphan*/  gethostname (char*,int) ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

void
shrink_hostname (const char *hostname,
		 char *dst, size_t dst_sz)
{
    char local_hostname[MaxHostNameLen];
    char *ld, *hd;
    int ret;
    struct addrinfo *ai;

    if (strlen(hostname) < dst_sz) {
	strlcpy (dst, hostname, dst_sz);
	return;
    }
    gethostname (local_hostname, sizeof(local_hostname));
    hd = strchr (hostname, '.');
    ld = strchr (local_hostname, '.');
    if (hd != NULL && ld != NULL && strcmp(hd, ld) == 0
	&& hd - hostname < dst_sz) {
	strlcpy (dst, hostname, dst_sz);
	dst[hd - hostname] = '\0';
	return;
    }

    ret = getaddrinfo (hostname, NULL, NULL, &ai);
    if (ret) {
	strncpy (dst, hostname, dst_sz);
	return;
    }
    ret = getnameinfo (ai->ai_addr, ai->ai_addrlen,
		       dst, dst_sz,
		       NULL, 0,
		       NI_NUMERICHOST);
    freeaddrinfo (ai);
    if (ret) {
	strncpy (dst, hostname, dst_sz);
	return;
    }
}