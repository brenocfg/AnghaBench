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
struct option {char* member_0; char member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  const member_1; } ;
struct addrinfo {int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;
typedef  int /*<<< orphan*/  reuseaddr_flag ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_2__ {int /*<<< orphan*/  max_cwnd; int /*<<< orphan*/  min_rtt; } ;
typedef  int /*<<< orphan*/  EC_KEY ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AI_ADDRCONFIG ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_new_by_curve_name (int) ; 
 int /*<<< orphan*/  H2O_SOCKET_FLAG_DONT_READ ; 
 int /*<<< orphan*/  INT32_MAX ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int NID_X9_62_prime256v1 ; 
 char* OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  OpenSSL_add_all_algorithms () ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_set_cipher_list (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_CTX_set_options (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SSL_CTX_set_tmp_ecdh (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_CTX_use_certificate_chain_file (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 int SSL_OP_ALL ; 
 int SSL_OP_NO_SSLv2 ; 
 int SSL_OP_NO_SSLv3 ; 
 int /*<<< orphan*/  SSL_library_init () ; 
 int /*<<< orphan*/  SSL_load_error_strings () ; 
 int /*<<< orphan*/  SSLv23_client_method () ; 
 int /*<<< orphan*/  SSLv23_server_method () ; 
 int /*<<< orphan*/  UV_RUN_DEFAULT ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 char* gai_strerror (int) ; 
 int getaddrinfo (char*,char*,struct addrinfo*,struct addrinfo**) ; 
 int getopt_long (int,char**,char*,struct option const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_evloop_create () ; 
 int /*<<< orphan*/  h2o_evloop_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_evloop_socket_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * h2o_socket_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_read_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* host ; 
 TYPE_1__ latopt_cond ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loop ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int mode_server ; 
#define  no_argument 129 
 int /*<<< orphan*/  on_accept ; 
 int /*<<< orphan*/  on_connect ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 char* port ; 
#define  required_argument 128 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * sock ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sscanf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_ctx ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 char* strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  uv_loop_new () ; 
 int /*<<< orphan*/  uv_run (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_block_size ; 

int main(int argc, char **argv)
{
    static const struct option longopts[] = {{"listen", no_argument, NULL, 'l'},
                                             {"reverse-role", no_argument, NULL, 'r'},
                                             {"tls", no_argument, NULL, 't'},
                                             {"block-size", no_argument, NULL, 'b'},
                                             {"min-rtt", required_argument, NULL, 'R'},
                                             {"max-cwnd", required_argument, NULL, 'c'},
                                             {}};
    int opt_ch, mode_listen = 0, mode_reverse_role = 0, mode_tls = 0;
    struct addrinfo hints, *res = NULL;
    int err;

    while ((opt_ch = getopt_long(argc, argv, "lrtb:R:c:", longopts, NULL)) != -1) {
        switch (opt_ch) {
        case 'l':
            mode_listen = 1;
            break;
        case 'r':
            mode_reverse_role = 1;
            break;
        case 't':
            mode_tls = 1;
            break;
        case 'b':
            if (sscanf(optarg, "%zu", &write_block_size) != 1) {
                fprintf(stderr, "write block size (-b) must be a non-negative number of octets\n");
                exit(1);
            }
            break;
        case 'R':
            if (sscanf(optarg, "%u", &latopt_cond.min_rtt) != 1) {
                fprintf(stderr, "min RTT (-m) must be a non-negative number in milliseconds\n");
                exit(1);
            }
            break;
        case 'c':
            if (sscanf(optarg, "%u", &latopt_cond.max_cwnd) != 1) {
                fprintf(stderr, "max CWND size must be a non-negative number of octets\n");
                exit(1);
            }
            break;
        default:
            usage(argv[0]);
            break;
        }
    }
    mode_server = mode_listen;
    if (mode_reverse_role)
        mode_server = !mode_server;

    if (argc == optind) {
        usage(argv[0]);
    } else {
        char *hostport = argv[optind], *colon;
        if ((colon = strchr(hostport, ':')) != NULL) {
            hostport = argv[optind];
            host = strdup(hostport);
            host[colon - hostport] = '\0';
            port = colon + 1;
        } else {
            host = "0.0.0.0";
            port = argv[optind];
        }
    }

    if (mode_tls) {
        SSL_load_error_strings();
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        if (mode_server) {
            ssl_ctx = SSL_CTX_new(SSLv23_server_method());
            SSL_CTX_use_certificate_chain_file(ssl_ctx, "examples/h2o/server.crt");
            SSL_CTX_use_PrivateKey_file(ssl_ctx, "examples/h2o/server.key", SSL_FILETYPE_PEM);
        } else {
            ssl_ctx = SSL_CTX_new(SSLv23_client_method());
        }
        int nid = NID_X9_62_prime256v1;
        EC_KEY *key = EC_KEY_new_by_curve_name(nid);
        if (key == NULL) {
            fprintf(stderr, "Failed to create curve \"%s\"\n", OBJ_nid2sn(nid));
            exit(1);
        }
        SSL_CTX_set_tmp_ecdh(ssl_ctx, key);
        EC_KEY_free(key);
        SSL_CTX_set_options(ssl_ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3);
        SSL_CTX_set_cipher_list(ssl_ctx, "ECDHE-RSA-AES128-GCM-SHA256");
    }

#if H2O_USE_LIBUV
    loop = uv_loop_new();
#else
    loop = h2o_evloop_create();
#endif

    /* resolve host:port (FIXME use the function supplied by the loop) */
    memset(&hints, 0, sizeof(hints));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_ADDRCONFIG;
    if ((err = getaddrinfo(host, port, &hints, &res)) != 0) {
        fprintf(stderr, "failed to resolve %s:%s:%s\n", host, port, gai_strerror(err));
        exit(1);
    }

    if (mode_listen) {
        int fd, reuseaddr_flag = 1;
        if ((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1 ||
            setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuseaddr_flag, sizeof(reuseaddr_flag)) != 0 ||
            bind(fd, res->ai_addr, res->ai_addrlen) != 0 || listen(fd, SOMAXCONN) != 0) {
            fprintf(stderr, "failed to listen to %s:%s:%s\n", host, port, strerror(errno));
            exit(1);
        }
        h2o_socket_t *listen_sock = h2o_evloop_socket_create(loop, fd, H2O_SOCKET_FLAG_DONT_READ);
        h2o_socket_read_start(listen_sock, on_accept);
    } else {
        if ((sock = h2o_socket_connect(loop, res->ai_addr, res->ai_addrlen, on_connect)) == NULL) {
            fprintf(stderr, "failed to create socket:%s\n", strerror(errno));
            exit(1);
        }
    }

    while (1) {
#if H2O_USE_LIBUV
        uv_run(loop, UV_RUN_DEFAULT);
#else
        h2o_evloop_run(loop, INT32_MAX);
#endif
    }

    return 0;
}