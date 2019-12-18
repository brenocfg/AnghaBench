#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct expbuf_t {int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  auth_token ;
struct TYPE_4__ {TYPE_1__* nb; } ;
struct TYPE_3__ {int /*<<< orphan*/  auth_token; } ;

/* Variables and functions */
 int NEVERBLEED_AUTH_TOKEN_SIZE ; 
 int /*<<< orphan*/  close (int) ; 
 TYPE_2__ daemon_vars ; 
 scalar_t__ del_ecdsa_key_stub (struct expbuf_t*) ; 
 scalar_t__ del_rsa_key_stub (struct expbuf_t*) ; 
 scalar_t__ ecdsa_sign_stub (struct expbuf_t*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  expbuf_dispose (struct expbuf_t*) ; 
 scalar_t__ expbuf_read (struct expbuf_t*,int) ; 
 char* expbuf_shift_str (struct expbuf_t*) ; 
 scalar_t__ expbuf_write (struct expbuf_t*,int) ; 
 scalar_t__ load_key_stub (struct expbuf_t*) ; 
 scalar_t__ memcmp (unsigned char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ priv_dec_stub (struct expbuf_t*) ; 
 scalar_t__ priv_enc_stub (struct expbuf_t*) ; 
 scalar_t__ read_nbytes (int,unsigned char**,int) ; 
 scalar_t__ setuidgid_stub (struct expbuf_t*) ; 
 scalar_t__ sign_stub (struct expbuf_t*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  warnf (char*,...) ; 

__attribute__((used)) static void *daemon_conn_thread(void *_sock_fd)
{
    int sock_fd = (int)((char *)_sock_fd - (char *)NULL);
    struct expbuf_t buf = {NULL};
    unsigned char auth_token[NEVERBLEED_AUTH_TOKEN_SIZE];

    /* authenticate */
    if (read_nbytes(sock_fd, &auth_token, sizeof(auth_token)) != 0) {
        warnf("failed to receive authencication token from client");
        goto Exit;
    }
    if (memcmp(auth_token, daemon_vars.nb->auth_token, NEVERBLEED_AUTH_TOKEN_SIZE) != 0) {
        warnf("client authentication failed");
        goto Exit;
    }

    while (1) {
        char *cmd;
        if (expbuf_read(&buf, sock_fd) != 0) {
            if (errno != 0)
                warnf("read error");
            break;
        }
        if ((cmd = expbuf_shift_str(&buf)) == NULL) {
            errno = 0;
            warnf("failed to parse request");
            break;
        }
        if (strcmp(cmd, "priv_enc") == 0) {
            if (priv_enc_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "priv_dec") == 0) {
            if (priv_dec_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "sign") == 0) {
            if (sign_stub(&buf) != 0)
                break;
#if OPENSSL_1_1_API
        } else if (strcmp(cmd, "ecdsa_sign") == 0) {
            if (ecdsa_sign_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "del_ecdsa_key") == 0) {
            if (del_ecdsa_key_stub(&buf) != 0)
                break;
#endif
        } else if (strcmp(cmd, "load_key") == 0) {
            if (load_key_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "del_rsa_key") == 0) {
            if (del_rsa_key_stub(&buf) != 0)
                break;
        } else if (strcmp(cmd, "setuidgid") == 0) {
            if (setuidgid_stub(&buf) != 0)
                break;
        } else {
            warnf("unknown command:%s", cmd);
            break;
        }
        if (expbuf_write(&buf, sock_fd) != 0) {
            warnf(errno != 0 ? "write error" : "connection closed by client");
            break;
        }
        expbuf_dispose(&buf);
    }

Exit:
    expbuf_dispose(&buf);
    close(sock_fd);

    return NULL;
}