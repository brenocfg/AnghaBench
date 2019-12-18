#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serv ;
typedef  int /*<<< orphan*/  host ;
struct TYPE_7__ {int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; } ;
struct TYPE_8__ {TYPE_1__ s_in; } ;
typedef  TYPE_2__ BIO_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_ADDR_rawport (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BIO_ADDR_sockaddr (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BIO_ADDR_sockaddr_size (TYPE_2__ const*) ; 
 int /*<<< orphan*/  BIO_F_ADDR_STRINGS ; 
 int /*<<< orphan*/  BIO_snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int BIO_sock_init () ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EAI_SYSTEM ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_SYS_LIB ; 
 int /*<<< orphan*/  ERR_add_error_data (int,int /*<<< orphan*/ ) ; 
 int NI_MAXHOST ; 
 int NI_MAXSERV ; 
 int NI_NUMERICHOST ; 
 int NI_NUMERICSERV ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_strdup (char*) ; 
 int /*<<< orphan*/  SYS_F_GETNAMEINFO ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int getnameinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int,int) ; 
 char* inet_ntoa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int addr_strings(const BIO_ADDR *ap, int numeric,
                        char **hostname, char **service)
{
    if (BIO_sock_init() != 1)
        return 0;

    if (1) {
#ifdef AI_PASSIVE
        int ret = 0;
        char host[NI_MAXHOST] = "", serv[NI_MAXSERV] = "";
        int flags = 0;

        if (numeric)
            flags |= NI_NUMERICHOST | NI_NUMERICSERV;

        if ((ret = getnameinfo(BIO_ADDR_sockaddr(ap),
                               BIO_ADDR_sockaddr_size(ap),
                               host, sizeof(host), serv, sizeof(serv),
                               flags)) != 0) {
# ifdef EAI_SYSTEM
            if (ret == EAI_SYSTEM) {
                SYSerr(SYS_F_GETNAMEINFO, get_last_socket_error());
                BIOerr(BIO_F_ADDR_STRINGS, ERR_R_SYS_LIB);
            } else
# endif
            {
                BIOerr(BIO_F_ADDR_STRINGS, ERR_R_SYS_LIB);
                ERR_add_error_data(1, gai_strerror(ret));
            }
            return 0;
        }

        /* VMS getnameinfo() has a bug, it doesn't fill in serv, which
         * leaves it with whatever garbage that happens to be there.
         * However, we initialise serv with the empty string (serv[0]
         * is therefore NUL), so it gets real easy to detect when things
         * didn't go the way one might expect.
         */
        if (serv[0] == '\0') {
            BIO_snprintf(serv, sizeof(serv), "%d",
                         ntohs(BIO_ADDR_rawport(ap)));
        }

        if (hostname != NULL)
            *hostname = OPENSSL_strdup(host);
        if (service != NULL)
            *service = OPENSSL_strdup(serv);
    } else {
#endif
        if (hostname != NULL)
            *hostname = OPENSSL_strdup(inet_ntoa(ap->s_in.sin_addr));
        if (service != NULL) {
            char serv[6];        /* port is 16 bits => max 5 decimal digits */
            BIO_snprintf(serv, sizeof(serv), "%d", ntohs(ap->s_in.sin_port));
            *service = OPENSSL_strdup(serv);
        }
    }

    if ((hostname != NULL && *hostname == NULL)
            || (service != NULL && *service == NULL)) {
        if (hostname != NULL) {
            OPENSSL_free(*hostname);
            *hostname = NULL;
        }
        if (service != NULL) {
            OPENSSL_free(*service);
            *service = NULL;
        }
        BIOerr(BIO_F_ADDR_STRINGS, ERR_R_MALLOC_FAILURE);
        return 0;
    }

    return 1;
}