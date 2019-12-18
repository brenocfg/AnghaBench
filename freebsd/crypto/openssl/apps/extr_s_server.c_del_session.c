#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int idlen; struct TYPE_5__* der; struct TYPE_5__* id; struct TYPE_5__* next; } ;
typedef  TYPE_1__ simple_ssl_session ;
typedef  int /*<<< orphan*/  SSL_SESSION ;
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 unsigned char* SSL_SESSION_get_id (int /*<<< orphan*/ *,unsigned int*) ; 
 TYPE_1__* first ; 
 int /*<<< orphan*/  memcmp (TYPE_1__*,unsigned char const*,unsigned int) ; 

__attribute__((used)) static void del_session(SSL_CTX *sctx, SSL_SESSION *session)
{
    simple_ssl_session *sess, *prev = NULL;
    const unsigned char *id;
    unsigned int idlen;
    id = SSL_SESSION_get_id(session, &idlen);
    for (sess = first; sess; sess = sess->next) {
        if (idlen == sess->idlen && !memcmp(sess->id, id, idlen)) {
            if (prev)
                prev->next = sess->next;
            else
                first = sess->next;
            OPENSSL_free(sess->id);
            OPENSSL_free(sess->der);
            OPENSSL_free(sess);
            return;
        }
        prev = sess;
    }
}