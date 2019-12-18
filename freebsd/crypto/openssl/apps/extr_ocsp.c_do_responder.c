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
typedef  int /*<<< orphan*/  reqbuf ;
typedef  int /*<<< orphan*/  inbuf ;
typedef  int /*<<< orphan*/  OCSP_REQUEST ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_FLAGS_BASE64_NO_NL ; 
 scalar_t__ BIO_do_accept (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_f_base64 () ; 
 int /*<<< orphan*/  BIO_free_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_get_fd (int /*<<< orphan*/ *,int*) ; 
 char* BIO_get_peer_name (int /*<<< orphan*/ *) ; 
 int BIO_gets (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * BIO_new_mem_buf (char*,int) ; 
 int /*<<< orphan*/ * BIO_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BIO_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int acfd ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/ * d2i_OCSP_REQUEST_bio (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_message (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int urldecode (char*) ; 

__attribute__((used)) static int do_responder(OCSP_REQUEST **preq, BIO **pcbio, BIO *acbio,
                        int timeout)
{
# ifdef OPENSSL_NO_SOCK
    return 0;
# else
    int len;
    OCSP_REQUEST *req = NULL;
    char inbuf[2048], reqbuf[2048];
    char *p, *q;
    BIO *cbio = NULL, *getbio = NULL, *b64 = NULL;
    const char *client;

    *preq = NULL;

    /* Connection loss before accept() is routine, ignore silently */
    if (BIO_do_accept(acbio) <= 0)
        return 0;

    cbio = BIO_pop(acbio);
    *pcbio = cbio;
    client = BIO_get_peer_name(cbio);

#  ifdef OCSP_DAEMON
    if (timeout > 0) {
        (void) BIO_get_fd(cbio, &acfd);
        alarm(timeout);
    }
#  endif

    /* Read the request line. */
    len = BIO_gets(cbio, reqbuf, sizeof(reqbuf));
    if (len <= 0)
        goto out;

    if (strncmp(reqbuf, "GET ", 4) == 0) {
        /* Expecting GET {sp} /URL {sp} HTTP/1.x */
        for (p = reqbuf + 4; *p == ' '; ++p)
            continue;
        if (*p != '/') {
            log_message(LOG_INFO, "Invalid request -- bad URL: %s", client);
            goto out;
        }
        p++;

        /* Splice off the HTTP version identifier. */
        for (q = p; *q; q++)
            if (*q == ' ')
                break;
        if (strncmp(q, " HTTP/1.", 8) != 0) {
            log_message(LOG_INFO,
                        "Invalid request -- bad HTTP version: %s", client);
            goto out;
        }
        *q = '\0';

        /*
         * Skip "GET / HTTP..." requests often used by load-balancers.  Note:
         * 'p' was incremented above to point to the first byte *after* the
         * leading slash, so with 'GET / ' it is now an empty string.
         */
        if (p[0] == '\0')
            goto out;

        len = urldecode(p);
        if (len <= 0) {
            log_message(LOG_INFO,
                        "Invalid request -- bad URL encoding: %s", client);
            goto out;
        }
        if ((getbio = BIO_new_mem_buf(p, len)) == NULL
            || (b64 = BIO_new(BIO_f_base64())) == NULL) {
            log_message(LOG_ERR, "Could not allocate base64 bio: %s", client);
            goto out;
        }
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
        getbio = BIO_push(b64, getbio);
    } else if (strncmp(reqbuf, "POST ", 5) != 0) {
        log_message(LOG_INFO, "Invalid request -- bad HTTP verb: %s", client);
        goto out;
    }

    /* Read and skip past the headers. */
    for (;;) {
        len = BIO_gets(cbio, inbuf, sizeof(inbuf));
        if (len <= 0)
            goto out;
        if ((inbuf[0] == '\r') || (inbuf[0] == '\n'))
            break;
    }

#  ifdef OCSP_DAEMON
    /* Clear alarm before we close the client socket */
    alarm(0);
    timeout = 0;
#  endif

    /* Try to read OCSP request */
    if (getbio != NULL) {
        req = d2i_OCSP_REQUEST_bio(getbio, NULL);
        BIO_free_all(getbio);
    } else {
        req = d2i_OCSP_REQUEST_bio(cbio, NULL);
    }

    if (req == NULL)
        log_message(LOG_ERR, "Error parsing OCSP request");

    *preq = req;

out:
#  ifdef OCSP_DAEMON
    if (timeout > 0)
        alarm(0);
    acfd = (int)INVALID_SOCKET;
#  endif
    return 1;
# endif
}