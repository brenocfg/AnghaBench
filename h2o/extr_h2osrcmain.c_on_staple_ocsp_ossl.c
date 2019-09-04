#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__* data; } ;
struct TYPE_6__ {TYPE_2__ response; } ;
struct listener_ssl_config_t {TYPE_3__ ocsp_stapling; } ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 void* CRYPTO_malloc (int,char*,int) ; 
 int SSL_TLSEXT_ERR_NOACK ; 
 int SSL_TLSEXT_ERR_OK ; 
 int /*<<< orphan*/  SSL_set_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_staple_ocsp_ossl(SSL *ssl, void *_ssl_conf)
{
    struct listener_ssl_config_t *ssl_conf = _ssl_conf;
    void *resp = NULL;
    size_t len = 0;

    /* fetch ocsp response */
    pthread_mutex_lock(&ssl_conf->ocsp_stapling.response.mutex);
    if (ssl_conf->ocsp_stapling.response.data != NULL) {
        resp = CRYPTO_malloc((int)ssl_conf->ocsp_stapling.response.data->size, __FILE__, __LINE__);
        if (resp != NULL) {
            len = ssl_conf->ocsp_stapling.response.data->size;
            memcpy(resp, ssl_conf->ocsp_stapling.response.data->bytes, len);
        }
    }
    pthread_mutex_unlock(&ssl_conf->ocsp_stapling.response.mutex);

    if (resp != NULL) {
        SSL_set_tlsext_status_ocsp_resp(ssl, resp, len);
        return SSL_TLSEXT_ERR_OK;
    } else {
        return SSL_TLSEXT_ERR_NOACK;
    }
}