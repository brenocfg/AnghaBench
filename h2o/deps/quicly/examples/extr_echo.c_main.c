#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int /*<<< orphan*/  ss_family; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  reuseaddr ;
typedef  int /*<<< orphan*/  quicly_stream_t ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ quicly_stream_open_t ;
typedef  int /*<<< orphan*/  quicly_conn_t ;
struct TYPE_13__ {int /*<<< orphan*/  super; } ;
typedef  TYPE_3__ ptls_openssl_sign_certificate_t ;
struct TYPE_11__ {scalar_t__ count; } ;
struct TYPE_14__ {int /*<<< orphan*/ * sign_certificate; TYPE_1__ certificates; int /*<<< orphan*/  cipher_suites; int /*<<< orphan*/  key_exchanges; int /*<<< orphan*/ * get_time; int /*<<< orphan*/  random_bytes; } ;
typedef  TYPE_4__ ptls_context_t ;
typedef  int /*<<< orphan*/  local ;
struct TYPE_15__ {TYPE_2__* stream_open; TYPE_4__* tls; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * PEM_read_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 TYPE_5__ ctx ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ is_server () ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  next_cid ; 
 int /*<<< orphan*/  on_stream_open ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  ptls_get_time ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ptls_load_certificates (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  ptls_openssl_cipher_suites ; 
 int /*<<< orphan*/  ptls_openssl_init_sign_certificate (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ptls_openssl_key_exchanges ; 
 int /*<<< orphan*/  ptls_openssl_random_bytes ; 
 int /*<<< orphan*/  quicly_amend_ptls_context (TYPE_4__*) ; 
 int quicly_connect (int /*<<< orphan*/ **,TYPE_5__*,char*,int /*<<< orphan*/ *,struct sockaddr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quicly_open_stream (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_5__ quicly_spec_context ; 
 scalar_t__ resolve_address (struct sockaddr*,int*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int run_loop (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 

int main(int argc, char **argv)
{
    ptls_openssl_sign_certificate_t sign_certificate;
    ptls_context_t tlsctx = {
        .random_bytes = ptls_openssl_random_bytes,
        .get_time = &ptls_get_time,
        .key_exchanges = ptls_openssl_key_exchanges,
        .cipher_suites = ptls_openssl_cipher_suites,
    };
    quicly_stream_open_t stream_open = {on_stream_open};
    char *host = "127.0.0.1", *port = "4433";
    struct sockaddr_storage sa;
    socklen_t salen;
    int ch, fd;

    /* setup quic context */
    ctx = quicly_spec_context;
    ctx.tls = &tlsctx;
    quicly_amend_ptls_context(ctx.tls);
    ctx.stream_open = &stream_open;

    /* resolve command line options and arguments */
    while ((ch = getopt(argc, argv, "c:k:p:h")) != -1) {
        switch (ch) {
        case 'c': /* load certificate chain */ {
            int ret;
            if ((ret = ptls_load_certificates(&tlsctx, optarg)) != 0) {
                fprintf(stderr, "failed to load certificates from file %s:%d\n", optarg, ret);
                exit(1);
            }
        } break;
        case 'k': /* load private key */ {
            FILE *fp;
            if ((fp = fopen(optarg, "r")) == NULL) {
                fprintf(stderr, "failed to open file:%s:%s\n", optarg, strerror(errno));
                exit(1);
            }
            EVP_PKEY *pkey = PEM_read_PrivateKey(fp, NULL, NULL, NULL);
            fclose(fp);
            if (pkey == NULL) {
                fprintf(stderr, "failed to load private key from file:%s\n", optarg);
                exit(1);
            }
            ptls_openssl_init_sign_certificate(&sign_certificate, pkey);
            EVP_PKEY_free(pkey);
            tlsctx.sign_certificate = &sign_certificate.super;
        } break;
        case 'p': /* port */
            port = optarg;
            break;
        case 'h': /* help */
            usage(argv[0]);
            break;
        default:
            exit(1);
            break;
        }
    }
    if ((tlsctx.certificates.count != 0) != (tlsctx.sign_certificate != NULL)) {
        fprintf(stderr, "-c and -k options must be used together\n");
        exit(1);
    }
    argc -= optind;
    argv += optind;
    if (argc != 0)
        host = *argv++;
    if (resolve_address((struct sockaddr *)&sa, &salen, host, port, AF_INET, SOCK_DGRAM, 0) != 0)
        exit(1);

    /* open socket, on the specified port (as a server), or on any port (as a client) */
    if ((fd = socket(sa.ss_family, SOCK_DGRAM, 0)) == -1) {
        perror("socket(2) failed");
        exit(1);
    }
    //fcntl(fd, F_SETFL, O_NONBLOCK);
    if (is_server()) {
        int reuseaddr = 1;
        setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr, sizeof(reuseaddr));
        if (bind(fd, (struct sockaddr *)&sa, salen) != 0) {
            perror("bind(2) failed");
            exit(1);
        }
    } else {
        struct sockaddr_in local;
        memset(&local, 0, sizeof(local));
        if (bind(fd, (struct sockaddr *)&local, sizeof(local)) != 0) {
            perror("bind(2) failed");
            exit(1);
        }
    }

    quicly_conn_t *client = NULL;
    if (!is_server()) {
        /* initiate a connection, and open a stream */
        int ret;
        if ((ret = quicly_connect(&client, &ctx, host, NULL, (struct sockaddr *)&sa, &next_cid, ptls_iovec_init(NULL, 0), NULL,
                                  NULL)) != 0) {
            fprintf(stderr, "quicly_connect failed:%d\n", ret);
            exit(1);
        }
        quicly_stream_t *stream; /* we retain the opened stream via the on_stream_open callback */
        quicly_open_stream(client, &stream, 0);
    }

    /* enter the event loop with a connection object */
    return run_loop(fd, client);
}