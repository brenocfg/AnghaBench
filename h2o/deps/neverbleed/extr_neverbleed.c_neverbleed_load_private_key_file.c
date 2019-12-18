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
struct st_neverbleed_thread_data_t {int /*<<< orphan*/  fd; } ;
struct expbuf_t {int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  neverbleed_t ;
typedef  int /*<<< orphan*/  SSL_CTX ;
typedef  int /*<<< orphan*/  EVP_PKEY ;

/* Variables and functions */
 int /*<<< orphan*/  EVP_PKEY_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NEVERBLEED_ERRBUF_SIZE ; 
#define  NEVERBLEED_TYPE_ECDSA 129 
#define  NEVERBLEED_TYPE_RSA 128 
 int SSL_CTX_use_PrivateKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * create_pkey (int /*<<< orphan*/ *,size_t,char*,char*) ; 
 int /*<<< orphan*/  dief (char*) ; 
 int /*<<< orphan*/ * ecdsa_create_pkey (int /*<<< orphan*/ *,size_t,size_t,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  expbuf_dispose (struct expbuf_t*) ; 
 int /*<<< orphan*/  expbuf_push_str (struct expbuf_t*,char const*) ; 
 scalar_t__ expbuf_read (struct expbuf_t*,int /*<<< orphan*/ ) ; 
 scalar_t__ expbuf_shift_num (struct expbuf_t*,size_t*) ; 
 char* expbuf_shift_str (struct expbuf_t*) ; 
 scalar_t__ expbuf_write (struct expbuf_t*,int /*<<< orphan*/ ) ; 
 struct st_neverbleed_thread_data_t* get_thread_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,...) ; 

int neverbleed_load_private_key_file(neverbleed_t *nb, SSL_CTX *ctx, const char *fn, char *errbuf)
{
    struct st_neverbleed_thread_data_t *thdata = get_thread_data(nb);
    struct expbuf_t buf = {NULL};
    int ret = 1;
    size_t index, type;
    EVP_PKEY *pkey;

    expbuf_push_str(&buf, "load_key");
    expbuf_push_str(&buf, fn);
    if (expbuf_write(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "write error" : "connection closed by daemon");
    expbuf_dispose(&buf);

    if (expbuf_read(&buf, thdata->fd) != 0)
        dief(errno != 0 ? "read error" : "connection closed by daemon");
    if (expbuf_shift_num(&buf, &type) != 0 || expbuf_shift_num(&buf, &index) != 0) {
        errno = 0;
        dief("failed to parse response");
    }

    switch (type) {
    case NEVERBLEED_TYPE_RSA: {
        char *estr, *nstr;

        if ((estr = expbuf_shift_str(&buf)) == NULL || (nstr = expbuf_shift_str(&buf)) == NULL) {
            errno = 0;
            dief("failed to parse response");
        }
        pkey = create_pkey(nb, index, estr, nstr);
        break;
    }
#if OPENSSL_1_1_API
    case NEVERBLEED_TYPE_ECDSA: {
        char *ec_pubkeystr;
        size_t curve_name;

        if (expbuf_shift_num(&buf, &curve_name) != 0 || (ec_pubkeystr = expbuf_shift_str(&buf)) == NULL) {
            errno = 0;
            dief("failed to parse response");
        }
        pkey = ecdsa_create_pkey(nb, index, curve_name, ec_pubkeystr);
        break;
    }
#endif
    default: {
        char *errstr;

        if ((errstr = expbuf_shift_str(&buf)) == NULL) {
            errno = 0;
            dief("failed to parse response");
        }

        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "%s", errstr);
        return -1;
    }
    }

    expbuf_dispose(&buf);

    /* success */
    if (SSL_CTX_use_PrivateKey(ctx, pkey) != 1) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "SSL_CTX_use_PrivateKey failed");
        ret = 0;
    }

    EVP_PKEY_free(pkey);
    return ret;
}