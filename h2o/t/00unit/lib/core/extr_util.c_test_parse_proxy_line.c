#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {scalar_t__ ss_family; } ;
struct sockaddr_in6 {scalar_t__ sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct TYPE_2__ {scalar_t__ s_addr; } ;
struct sockaddr_in {scalar_t__ sin_port; TYPE_1__ sin_addr; } ;
typedef  int ssize_t ;
typedef  int socklen_t ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  H2O_STRLIT (char*) ; 
 scalar_t__ htonl (int) ; 
 scalar_t__ htons (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int) ; 
 int parse_proxy_line (char*,int,void*,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static void test_parse_proxy_line(void)
{
    char in[256];
    struct sockaddr_storage sa;
    socklen_t salen;
    ssize_t ret;

    strcpy(in, "");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == -2);

    strcpy(in, "PROXY TCP4 192.168.0.1 192.168.0.11 56324 443\r\nabc");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == strlen(in) - 3);
    ok(salen == sizeof(struct sockaddr_in));
    ok(sa.ss_family == AF_INET);
    ok(((struct sockaddr_in *)&sa)->sin_addr.s_addr == htonl(0xc0a80001));
    ok(((struct sockaddr_in *)&sa)->sin_port == htons(56324));

    strcpy(in, "PROXY TCP4 192.168.0.1 192.168.0.11 56324 443\r");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == -2);

    strcpy(in, "PROXY TCP5");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == -1);

    strcpy(in, "PROXY UNKNOWN");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == -2);

    strcpy(in, "PROXY UNKNOWN\r\nabc");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == strlen(in) - 3);
    ok(salen == 0);

    strcpy(in, "PROXY TCP6 ::1 ::1 56324 443\r\n");
    ret = parse_proxy_line(in, strlen(in), (void *)&sa, &salen);
    ok(ret == strlen(in));
    ok(salen == sizeof(struct sockaddr_in6));
    ok(sa.ss_family == AF_INET6);
    ok(memcmp(&((struct sockaddr_in6 *)&sa)->sin6_addr, H2O_STRLIT("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\1")) == 0);
    ok(((struct sockaddr_in6 *)&sa)->sin6_port == htons(56324));
}