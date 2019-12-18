#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {char* sun_path; int /*<<< orphan*/  sun_family; } ;
struct TYPE_21__ {int daemon_pid; int /*<<< orphan*/ * engine; int /*<<< orphan*/  thread_key; TYPE_5__ sun_; int /*<<< orphan*/  auth_token; } ;
typedef  TYPE_1__ neverbleed_t ;
struct TYPE_24__ {TYPE_1__* nb; } ;
struct TYPE_22__ {int /*<<< orphan*/  rsa_verify; int /*<<< orphan*/  rsa_pub_dec; int /*<<< orphan*/  rsa_pub_enc; } ;
typedef  TYPE_2__ RSA_METHOD ;
typedef  int /*<<< orphan*/  EC_KEY_METHOD ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/ * EC_KEY_METHOD_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_METHOD_set_compute_key (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_METHOD_set_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_METHOD_set_keygen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_KEY_METHOD_set_sign (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_KEY_get_default_method () ; 
 int /*<<< orphan*/  ENGINE_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ENGINE_new () ; 
 int /*<<< orphan*/  ENGINE_set_EC (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENGINE_set_RSA (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ENGINE_set_id (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ENGINE_set_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  NEVERBLEED_ERRBUF_SIZE ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  PR_SET_DUMPABLE ; 
 int /*<<< orphan*/  RAND_bytes (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* RSA_PKCS1_OpenSSL () ; 
 TYPE_2__* RSA_PKCS1_SSLeay () ; 
 int /*<<< orphan*/  RSA_meth_get_pub_dec (TYPE_2__ const*) ; 
 int /*<<< orphan*/  RSA_meth_get_pub_enc (TYPE_2__ const*) ; 
 int /*<<< orphan*/  RSA_meth_get_verify (TYPE_2__ const*) ; 
 TYPE_2__* RSA_meth_new (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_finish (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_priv_dec (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_priv_enc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_pub_dec (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_pub_enc (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_sign (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RSA_meth_set_verify (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOMAXCONN ; 
 scalar_t__ bind (int,void*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  daemon_main (int,int,char*) ; 
 TYPE_6__ daemon_vars ; 
 int /*<<< orphan*/  dispose_thread_data ; 
 int /*<<< orphan*/  ecdsa_sign_proxy ; 
 int /*<<< orphan*/  errno ; 
 int fork () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * mkdtemp (char*) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  prctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  priv_dec_proxy ; 
 int /*<<< orphan*/  priv_ecdsa_finish ; 
 int /*<<< orphan*/  priv_enc_proxy ; 
 int /*<<< orphan*/  priv_rsa_finish ; 
 int /*<<< orphan*/  pthread_key_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_cloexec (int) ; 
 int /*<<< orphan*/  sign_proxy ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ static_rsa_method ; 
 char* strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink_dir (char*) ; 

int neverbleed_init(neverbleed_t *nb, char *errbuf)
{
    int pipe_fds[2] = {-1, -1}, listen_fd = -1;
    char *tempdir = NULL;
#if OPENSSL_1_1_API
    const RSA_METHOD *default_method = RSA_PKCS1_OpenSSL();
    EC_KEY_METHOD *ecdsa_method;
    const EC_KEY_METHOD *ecdsa_default_method;
    RSA_METHOD *rsa_method = RSA_meth_new("privsep RSA method", 0);

    RSA_meth_set_priv_enc(rsa_method, priv_enc_proxy);
    RSA_meth_set_priv_dec(rsa_method, priv_dec_proxy);
    RSA_meth_set_sign(rsa_method, sign_proxy);

    RSA_meth_set_pub_enc(rsa_method, RSA_meth_get_pub_enc(default_method));
    RSA_meth_set_pub_dec(rsa_method, RSA_meth_get_pub_dec(default_method));
    RSA_meth_set_verify(rsa_method, RSA_meth_get_verify(default_method));

    RSA_meth_set_finish(rsa_method, priv_rsa_finish);

    /* setup EC_KEY_METHOD for ECDSA */
    ecdsa_default_method = EC_KEY_get_default_method();
    ecdsa_method = EC_KEY_METHOD_new(ecdsa_default_method);

    EC_KEY_METHOD_set_keygen(ecdsa_method, NULL);
    EC_KEY_METHOD_set_compute_key(ecdsa_method, NULL);
    /* it seems sign_sig and sign_setup is not used in TLS ECDSA. */
    EC_KEY_METHOD_set_sign(ecdsa_method, ecdsa_sign_proxy, NULL, NULL);
    EC_KEY_METHOD_set_init(ecdsa_method, NULL, priv_ecdsa_finish, NULL, NULL, NULL, NULL);
#else
    const RSA_METHOD *default_method = RSA_PKCS1_SSLeay();
    RSA_METHOD *rsa_method = &static_rsa_method;

    rsa_method->rsa_pub_enc = default_method->rsa_pub_enc;
    rsa_method->rsa_pub_dec = default_method->rsa_pub_dec;
    rsa_method->rsa_verify = default_method->rsa_verify;
#endif

    /* setup the daemon */
    if (pipe(pipe_fds) != 0) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "pipe(2) failed:%s", strerror(errno));
        goto Fail;
    }
    set_cloexec(pipe_fds[1]);
    if ((tempdir = strdup("/tmp/openssl-privsep.XXXXXX")) == NULL) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "no memory");
        goto Fail;
    }
    if (mkdtemp(tempdir) == NULL) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to create temporary directory under /tmp:%s", strerror(errno));
        goto Fail;
    }
    memset(&nb->sun_, 0, sizeof(nb->sun_));
    nb->sun_.sun_family = AF_UNIX;
    snprintf(nb->sun_.sun_path, sizeof(nb->sun_.sun_path), "%s/_", tempdir);
    RAND_bytes(nb->auth_token, sizeof(nb->auth_token));
    if ((listen_fd = socket(PF_UNIX, SOCK_STREAM, 0)) == -1) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "socket(2) failed:%s", strerror(errno));
        goto Fail;
    }
    if (bind(listen_fd, (void *)&nb->sun_, sizeof(nb->sun_)) != 0) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to bind to %s:%s", nb->sun_.sun_path, strerror(errno));
        goto Fail;
    }
    if (listen(listen_fd, SOMAXCONN) != 0) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "listen(2) failed:%s", strerror(errno));
        goto Fail;
    }
    nb->daemon_pid = fork();
    switch (nb->daemon_pid) {
    case -1:
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "fork(2) failed:%s", strerror(errno));
        goto Fail;
    case 0:
        close(pipe_fds[1]);
#ifdef __linux__
        prctl(PR_SET_DUMPABLE, 0, 0, 0, 0);
#endif
        daemon_vars.nb = nb;
        daemon_main(listen_fd, pipe_fds[0], tempdir);
        break;
    default:
        break;
    }
    close(listen_fd);
    listen_fd = -1;
    close(pipe_fds[0]);
    pipe_fds[0] = -1;

    /* setup engine */
    if ((nb->engine = ENGINE_new()) == NULL || !ENGINE_set_id(nb->engine, "neverbleed") ||
        !ENGINE_set_name(nb->engine, "privilege separation software engine") || !ENGINE_set_RSA(nb->engine, rsa_method)
#if OPENSSL_1_1_API
        || !ENGINE_set_EC(nb->engine, ecdsa_method)
#endif
            ) {
        snprintf(errbuf, NEVERBLEED_ERRBUF_SIZE, "failed to initialize the OpenSSL engine");
        goto Fail;
    }
    ENGINE_add(nb->engine);

    /* setup thread key */
    pthread_key_create(&nb->thread_key, dispose_thread_data);

    free(tempdir);
    return 0;
Fail:
    if (pipe_fds[0] != -1)
        close(pipe_fds[0]);
    if (pipe_fds[1] != -1)
        close(pipe_fds[1]);
    if (tempdir != NULL) {
        unlink_dir(tempdir);
        free(tempdir);
    }
    if (listen_fd != -1)
        close(listen_fd);
    if (nb->engine != NULL) {
        ENGINE_free(nb->engine);
        nb->engine = NULL;
    }
    return -1;
}