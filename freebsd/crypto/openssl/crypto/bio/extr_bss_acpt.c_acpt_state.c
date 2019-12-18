#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
union BIO_sock_info_u {int /*<<< orphan*/ * addr; } ;
struct TYPE_17__ {int num; int /*<<< orphan*/ * next_bio; int /*<<< orphan*/  retry_reason; } ;
struct TYPE_16__ {int state; int accept_sock; int /*<<< orphan*/  cache_peer_addr; int /*<<< orphan*/ * cache_peer_serv; int /*<<< orphan*/ * cache_peer_name; int /*<<< orphan*/ * bio_chain; int /*<<< orphan*/  accepted_mode; int /*<<< orphan*/  cache_accepting_addr; int /*<<< orphan*/ * cache_accepting_serv; int /*<<< orphan*/ * cache_accepting_name; int /*<<< orphan*/  bind_mode; int /*<<< orphan*/ * addr_iter; int /*<<< orphan*/ * param_serv; int /*<<< orphan*/ * param_addr; int /*<<< orphan*/ * addr_first; int /*<<< orphan*/  accept_family; } ;
typedef  TYPE_1__ BIO_ACCEPT ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
#define  ACPT_S_ACCEPT 136 
#define  ACPT_S_BEFORE 135 
#define  ACPT_S_CREATE_SOCKET 134 
#define  ACPT_S_GET_ADDR 133 
#define  ACPT_S_LISTEN 132 
#define  ACPT_S_OK 131 
 int AF_INET ; 
 int AF_INET6 ; 
 int AF_UNSPEC ; 
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_protocol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_socktype (int /*<<< orphan*/ *) ; 
 void* BIO_ADDR_hostname_string (int /*<<< orphan*/ *,int) ; 
 void* BIO_ADDR_service_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_CLOSE ; 
#define  BIO_FAMILY_IPANY 130 
#define  BIO_FAMILY_IPV4 129 
#define  BIO_FAMILY_IPV6 128 
 int /*<<< orphan*/  BIO_F_ACPT_STATE ; 
 int /*<<< orphan*/  BIO_LOOKUP_SERVER ; 
 int /*<<< orphan*/  BIO_RR_ACCEPT ; 
 int /*<<< orphan*/  BIO_R_LOOKUP_RETURNED_NOTHING ; 
 int /*<<< orphan*/  BIO_R_NO_ACCEPT_ADDR_OR_SERVICE_SPECIFIED ; 
 int /*<<< orphan*/  BIO_R_UNABLE_TO_CREATE_SOCKET ; 
 int /*<<< orphan*/  BIO_R_UNAVAILABLE_IP_FAMILY ; 
 int /*<<< orphan*/  BIO_R_UNSUPPORTED_IP_FAMILY ; 
 int /*<<< orphan*/  BIO_SOCK_INFO_ADDRESS ; 
 int BIO_accept_ex (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 TYPE_2__* BIO_dup_chain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_free (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_get_callback (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_get_callback_arg (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_listen (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 TYPE_2__* BIO_new_socket (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_push (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_set_callback (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_callback_arg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_set_retry_special (TYPE_2__*) ; 
 int /*<<< orphan*/  BIO_sock_info (int,int /*<<< orphan*/ ,union BIO_sock_info_u*) ; 
 int /*<<< orphan*/  BIO_sock_should_retry (int) ; 
 int BIO_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SYS_F_SOCKET ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 

__attribute__((used)) static int acpt_state(BIO *b, BIO_ACCEPT *c)
{
    BIO *bio = NULL, *dbio;
    int s = -1, ret = -1;

    for (;;) {
        switch (c->state) {
        case ACPT_S_BEFORE:
            if (c->param_addr == NULL && c->param_serv == NULL) {
                BIOerr(BIO_F_ACPT_STATE, BIO_R_NO_ACCEPT_ADDR_OR_SERVICE_SPECIFIED);
                ERR_add_error_data(4,
                                   "hostname=", c->param_addr,
                                   " service=", c->param_serv);
                goto exit_loop;
            }

            /* Because we're starting a new bind, any cached name and serv
             * are now obsolete and need to be cleaned out.
             * QUESTION: should this be done in acpt_close_socket() instead?
             */
            OPENSSL_free(c->cache_accepting_name);
            c->cache_accepting_name = NULL;
            OPENSSL_free(c->cache_accepting_serv);
            c->cache_accepting_serv = NULL;
            OPENSSL_free(c->cache_peer_name);
            c->cache_peer_name = NULL;
            OPENSSL_free(c->cache_peer_serv);
            c->cache_peer_serv = NULL;

            c->state = ACPT_S_GET_ADDR;
            break;

        case ACPT_S_GET_ADDR:
            {
                int family = AF_UNSPEC;
                switch (c->accept_family) {
                case BIO_FAMILY_IPV6:
                    if (1) { /* This is a trick we use to avoid bit rot.
                              * at least the "else" part will always be
                              * compiled.
                              */
#ifdef AF_INET6
                        family = AF_INET6;
                    } else {
#endif
                        BIOerr(BIO_F_ACPT_STATE, BIO_R_UNAVAILABLE_IP_FAMILY);
                        goto exit_loop;
                    }
                    break;
                case BIO_FAMILY_IPV4:
                    family = AF_INET;
                    break;
                case BIO_FAMILY_IPANY:
                    family = AF_UNSPEC;
                    break;
                default:
                    BIOerr(BIO_F_ACPT_STATE, BIO_R_UNSUPPORTED_IP_FAMILY);
                    goto exit_loop;
                }
                if (BIO_lookup(c->param_addr, c->param_serv, BIO_LOOKUP_SERVER,
                               family, SOCK_STREAM, &c->addr_first) == 0)
                    goto exit_loop;
            }
            if (c->addr_first == NULL) {
                BIOerr(BIO_F_ACPT_STATE, BIO_R_LOOKUP_RETURNED_NOTHING);
                goto exit_loop;
            }
            /* We're currently not iterating, but set this as preparation
             * for possible future development in that regard
             */
            c->addr_iter = c->addr_first;
            c->state = ACPT_S_CREATE_SOCKET;
            break;

        case ACPT_S_CREATE_SOCKET:
            ret = BIO_socket(BIO_ADDRINFO_family(c->addr_iter),
                             BIO_ADDRINFO_socktype(c->addr_iter),
                             BIO_ADDRINFO_protocol(c->addr_iter), 0);
            if (ret == (int)INVALID_SOCKET) {
                SYSerr(SYS_F_SOCKET, get_last_socket_error());
                ERR_add_error_data(4,
                                   "hostname=", c->param_addr,
                                   " service=", c->param_serv);
                BIOerr(BIO_F_ACPT_STATE, BIO_R_UNABLE_TO_CREATE_SOCKET);
                goto exit_loop;
            }
            c->accept_sock = ret;
            b->num = ret;
            c->state = ACPT_S_LISTEN;
            break;

        case ACPT_S_LISTEN:
            {
                if (!BIO_listen(c->accept_sock,
                                BIO_ADDRINFO_address(c->addr_iter),
                                c->bind_mode)) {
                    BIO_closesocket(c->accept_sock);
                    goto exit_loop;
                }
            }

            {
                union BIO_sock_info_u info;

                info.addr = &c->cache_accepting_addr;
                if (!BIO_sock_info(c->accept_sock, BIO_SOCK_INFO_ADDRESS,
                                   &info)) {
                    BIO_closesocket(c->accept_sock);
                    goto exit_loop;
                }
            }

            c->cache_accepting_name =
                BIO_ADDR_hostname_string(&c->cache_accepting_addr, 1);
            c->cache_accepting_serv =
                BIO_ADDR_service_string(&c->cache_accepting_addr, 1);
            c->state = ACPT_S_ACCEPT;
            s = -1;
            ret = 1;
            goto end;

        case ACPT_S_ACCEPT:
            if (b->next_bio != NULL) {
                c->state = ACPT_S_OK;
                break;
            }
            BIO_clear_retry_flags(b);
            b->retry_reason = 0;

            OPENSSL_free(c->cache_peer_name);
            c->cache_peer_name = NULL;
            OPENSSL_free(c->cache_peer_serv);
            c->cache_peer_serv = NULL;

            s = BIO_accept_ex(c->accept_sock, &c->cache_peer_addr,
                              c->accepted_mode);

            /* If the returned socket is invalid, this might still be
             * retryable
             */
            if (s < 0) {
                if (BIO_sock_should_retry(s)) {
                    BIO_set_retry_special(b);
                    b->retry_reason = BIO_RR_ACCEPT;
                    goto end;
                }
            }

            /* If it wasn't retryable, we fail */
            if (s < 0) {
                ret = s;
                goto exit_loop;
            }

            bio = BIO_new_socket(s, BIO_CLOSE);
            if (bio == NULL)
                goto exit_loop;

            BIO_set_callback(bio, BIO_get_callback(b));
            BIO_set_callback_arg(bio, BIO_get_callback_arg(b));

            /*
             * If the accept BIO has an bio_chain, we dup it and put the new
             * socket at the end.
             */
            if (c->bio_chain != NULL) {
                if ((dbio = BIO_dup_chain(c->bio_chain)) == NULL)
                    goto exit_loop;
                if (!BIO_push(dbio, bio))
                    goto exit_loop;
                bio = dbio;
            }
            if (BIO_push(b, bio) == NULL)
                goto exit_loop;

            c->cache_peer_name =
                BIO_ADDR_hostname_string(&c->cache_peer_addr, 1);
            c->cache_peer_serv =
                BIO_ADDR_service_string(&c->cache_peer_addr, 1);
            c->state = ACPT_S_OK;
            bio = NULL;
            ret = 1;
            goto end;

        case ACPT_S_OK:
            if (b->next_bio == NULL) {
                c->state = ACPT_S_ACCEPT;
                break;
            }
            ret = 1;
            goto end;

        default:
            ret = 0;
            goto end;
        }
    }

  exit_loop:
    if (bio != NULL)
        BIO_free(bio);
    else if (s >= 0)
        BIO_closesocket(s);
  end:
    return ret;
}