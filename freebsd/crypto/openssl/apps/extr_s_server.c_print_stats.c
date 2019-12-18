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
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  SSL_CTX_sess_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_accept_good (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_accept_renegotiate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_cache_full (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_cb_hits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_connect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_connect_good (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_connect_renegotiate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_get_cache_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_hits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_misses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_number (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SSL_CTX_sess_timeouts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void print_stats(BIO *bio, SSL_CTX *ssl_ctx)
{
    BIO_printf(bio, "%4ld items in the session cache\n",
               SSL_CTX_sess_number(ssl_ctx));
    BIO_printf(bio, "%4ld client connects (SSL_connect())\n",
               SSL_CTX_sess_connect(ssl_ctx));
    BIO_printf(bio, "%4ld client renegotiates (SSL_connect())\n",
               SSL_CTX_sess_connect_renegotiate(ssl_ctx));
    BIO_printf(bio, "%4ld client connects that finished\n",
               SSL_CTX_sess_connect_good(ssl_ctx));
    BIO_printf(bio, "%4ld server accepts (SSL_accept())\n",
               SSL_CTX_sess_accept(ssl_ctx));
    BIO_printf(bio, "%4ld server renegotiates (SSL_accept())\n",
               SSL_CTX_sess_accept_renegotiate(ssl_ctx));
    BIO_printf(bio, "%4ld server accepts that finished\n",
               SSL_CTX_sess_accept_good(ssl_ctx));
    BIO_printf(bio, "%4ld session cache hits\n", SSL_CTX_sess_hits(ssl_ctx));
    BIO_printf(bio, "%4ld session cache misses\n",
               SSL_CTX_sess_misses(ssl_ctx));
    BIO_printf(bio, "%4ld session cache timeouts\n",
               SSL_CTX_sess_timeouts(ssl_ctx));
    BIO_printf(bio, "%4ld callback cache hits\n",
               SSL_CTX_sess_cb_hits(ssl_ctx));
    BIO_printf(bio, "%4ld cache full overflows (%ld allowed)\n",
               SSL_CTX_sess_cache_full(ssl_ctx),
               SSL_CTX_sess_get_cache_size(ssl_ctx));
}