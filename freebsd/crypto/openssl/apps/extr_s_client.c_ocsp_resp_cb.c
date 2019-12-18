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
typedef  int /*<<< orphan*/  SSL ;
typedef  int /*<<< orphan*/  OCSP_RESPONSE ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_dump_indent (void*,char*,int,int) ; 
 int /*<<< orphan*/  BIO_puts (void*,char*) ; 
 int /*<<< orphan*/  OCSP_RESPONSE_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OCSP_RESPONSE_print (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int SSL_get_tlsext_status_ocsp_resp (int /*<<< orphan*/ *,unsigned char const**) ; 
 int /*<<< orphan*/ * d2i_OCSP_RESPONSE (int /*<<< orphan*/ *,unsigned char const**,int) ; 

__attribute__((used)) static int ocsp_resp_cb(SSL *s, void *arg)
{
    const unsigned char *p;
    int len;
    OCSP_RESPONSE *rsp;
    len = SSL_get_tlsext_status_ocsp_resp(s, &p);
    BIO_puts(arg, "OCSP response: ");
    if (p == NULL) {
        BIO_puts(arg, "no response sent\n");
        return 1;
    }
    rsp = d2i_OCSP_RESPONSE(NULL, &p, len);
    if (rsp == NULL) {
        BIO_puts(arg, "response parse error\n");
        BIO_dump_indent(arg, (char *)p, len, 4);
        return 0;
    }
    BIO_puts(arg, "\n======================================\n");
    OCSP_RESPONSE_print(arg, rsp, 0);
    BIO_puts(arg, "======================================\n");
    OCSP_RESPONSE_free(rsp);
    return 1;
}