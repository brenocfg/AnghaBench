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
struct linger {int l_onoff; scalar_t__ l_linger; } ;
typedef  int /*<<< orphan*/  no_linger ;
struct TYPE_2__ {scalar_t__ error; } ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_SOCK_NODELAY ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  BIO_s_connect () ; 
 int /*<<< orphan*/  BIO_set_conn_hostname (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  BIO_set_conn_mode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_print_errors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_LINGER ; 
 int SSL_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 int SSL_get_fd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * SSL_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_set_connect_state (int /*<<< orphan*/ *) ; 
 scalar_t__ X509_V_OK ; 
 int /*<<< orphan*/  X509_verify_cert_error_string (scalar_t__) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_1__ verify_args ; 

__attribute__((used)) static SSL *doConnection(SSL *scon, const char *host, SSL_CTX *ctx)
{
    BIO *conn;
    SSL *serverCon;
    int i;

    if ((conn = BIO_new(BIO_s_connect())) == NULL)
        return NULL;

    BIO_set_conn_hostname(conn, host);
    BIO_set_conn_mode(conn, BIO_SOCK_NODELAY);

    if (scon == NULL)
        serverCon = SSL_new(ctx);
    else {
        serverCon = scon;
        SSL_set_connect_state(serverCon);
    }

    SSL_set_bio(serverCon, conn, conn);

    /* ok, lets connect */
    i = SSL_connect(serverCon);
    if (i <= 0) {
        BIO_printf(bio_err, "ERROR\n");
        if (verify_args.error != X509_V_OK)
            BIO_printf(bio_err, "verify error:%s\n",
                       X509_verify_cert_error_string(verify_args.error));
        else
            ERR_print_errors(bio_err);
        if (scon == NULL)
            SSL_free(serverCon);
        return NULL;
    }

#if defined(SOL_SOCKET) && defined(SO_LINGER)
    {
        struct linger no_linger;
        int fd;

        no_linger.l_onoff  = 1;
        no_linger.l_linger = 0;
        fd = SSL_get_fd(serverCon);
        if (fd >= 0)
            (void)setsockopt(fd, SOL_SOCKET, SO_LINGER, (char*)&no_linger,
                             sizeof(no_linger));
    }
#endif

    return serverCon;
}