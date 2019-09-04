#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_socket_t ;
struct TYPE_3__ {scalar_t__ base; int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_get_data (int /*<<< orphan*/ ) ; 
 unsigned char* SSL_SESSION_get_id (int /*<<< orphan*/ *,unsigned int*) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ *) ; 
 scalar_t__ alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_iovec_init (unsigned char const*,unsigned int) ; 
 int /*<<< orphan*/  i2d_SSL_SESSION (int /*<<< orphan*/ *,unsigned char**) ; 
 int /*<<< orphan*/  resumption_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__) ; 

__attribute__((used)) static int on_async_resumption_new(SSL *ssl, SSL_SESSION *session)
{
    h2o_socket_t *sock = BIO_get_data(SSL_get_rbio(ssl));

    h2o_iovec_t data;
    const unsigned char *id;
    unsigned id_len;
    unsigned char *p;

    /* build data */
    data.len = i2d_SSL_SESSION(session, NULL);
    data.base = alloca(data.len);
    p = (void *)data.base;
    i2d_SSL_SESSION(session, &p);

    id = SSL_SESSION_get_id(session, &id_len);
    resumption_new(sock, h2o_iovec_init(id, id_len), data);
    return 0;
}