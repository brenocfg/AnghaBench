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
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; int /*<<< orphan*/  sin6_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct sockaddr {int /*<<< orphan*/  sa_family; } ;
typedef  int ssize_t ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  in_port_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  CHECK_EOF () ; 
 int /*<<< orphan*/  EXPECT_CHAR (char) ; 
 int /*<<< orphan*/  SKIP_TO_WS () ; 
 int /*<<< orphan*/  htons (unsigned short) ; 
 int inet_pton (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  memset (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char*,char*,unsigned short*) ; 

__attribute__((used)) static ssize_t parse_proxy_line(char *src, size_t len, struct sockaddr *sa, socklen_t *salen)
{
#define CHECK_EOF()                                                                                                                \
    if (p == end)                                                                                                                  \
    return -2
#define EXPECT_CHAR(ch)                                                                                                            \
    do {                                                                                                                           \
        CHECK_EOF();                                                                                                               \
        if (*p++ != ch)                                                                                                            \
            return -1;                                                                                                             \
    } while (0)
#define SKIP_TO_WS()                                                                                                               \
    do {                                                                                                                           \
        do {                                                                                                                       \
            CHECK_EOF();                                                                                                           \
        } while (*p++ != ' ');                                                                                                     \
        --p;                                                                                                                       \
    } while (0)

    char *p = src, *end = p + len;
    void *addr;
    in_port_t *port;

    /* "PROXY "*/
    EXPECT_CHAR('P');
    EXPECT_CHAR('R');
    EXPECT_CHAR('O');
    EXPECT_CHAR('X');
    EXPECT_CHAR('Y');
    EXPECT_CHAR(' ');

    /* "TCP[46] " */
    CHECK_EOF();
    if (*p++ != 'T') {
        *salen = 0; /* indicate that no data has been obtained */
        goto SkipToEOL;
    }
    EXPECT_CHAR('C');
    EXPECT_CHAR('P');
    CHECK_EOF();
    switch (*p++) {
    case '4':
        *salen = sizeof(struct sockaddr_in);
        memset(sa, 0, sizeof(struct sockaddr_in));
        sa->sa_family = AF_INET;
        addr = &((struct sockaddr_in *)sa)->sin_addr;
        port = &((struct sockaddr_in *)sa)->sin_port;
        break;
    case '6':
        *salen = sizeof(struct sockaddr_in6);
        memset(sa, 0, sizeof(struct sockaddr_in6));
        sa->sa_family = AF_INET6;
        addr = &((struct sockaddr_in6 *)sa)->sin6_addr;
        port = &((struct sockaddr_in6 *)sa)->sin6_port;
        break;
    default:
        return -1;
    }
    EXPECT_CHAR(' ');

    /* parse peer address */
    char *addr_start = p;
    SKIP_TO_WS();
    *p = '\0';
    if (inet_pton(sa->sa_family, addr_start, addr) != 1)
        return -1;
    *p++ = ' ';

    /* skip local address */
    SKIP_TO_WS();
    ++p;

    /* parse peer port */
    char *port_start = p;
    SKIP_TO_WS();
    *p = '\0';
    unsigned short usval;
    if (sscanf(port_start, "%hu", &usval) != 1)
        return -1;
    *port = htons(usval);
    *p++ = ' ';

SkipToEOL:
    do {
        CHECK_EOF();
    } while (*p++ != '\r');
    CHECK_EOF();
    if (*p++ != '\n')
        return -2;
    return p - src;

#undef CHECK_EOF
#undef EXPECT_CHAR
#undef SKIP_TO_WS
}