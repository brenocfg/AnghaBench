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
typedef  int /*<<< orphan*/  BIO_ADDR ;

/* Variables and functions */
 char* BIO_ADDR_hostname_string (int /*<<< orphan*/ *,int) ; 
 char* BIO_ADDR_service_string (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_F_BIO_ACCEPT ; 
 int /*<<< orphan*/  BIO_R_ACCEPT_ERROR ; 
 int BIO_accept_ex (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_closesocket (int) ; 
 scalar_t__ BIO_sock_should_retry (int) ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  OPENSSL_free (char*) ; 
 char* OPENSSL_zalloc (scalar_t__) ; 
 int /*<<< orphan*/  SYS_F_ACCEPT ; 
 int /*<<< orphan*/  SYSerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_socket_error () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

int BIO_accept(int sock, char **ip_port)
{
    BIO_ADDR res;
    int ret = -1;

    ret = BIO_accept_ex(sock, &res, 0);
    if (ret == (int)INVALID_SOCKET) {
        if (BIO_sock_should_retry(ret)) {
            ret = -2;
            goto end;
        }
        SYSerr(SYS_F_ACCEPT, get_last_socket_error());
        BIOerr(BIO_F_BIO_ACCEPT, BIO_R_ACCEPT_ERROR);
        goto end;
    }

    if (ip_port != NULL) {
        char *host = BIO_ADDR_hostname_string(&res, 1);
        char *port = BIO_ADDR_service_string(&res, 1);
        if (host != NULL && port != NULL)
            *ip_port = OPENSSL_zalloc(strlen(host) + strlen(port) + 2);
        else
            *ip_port = NULL;

        if (*ip_port == NULL) {
            BIOerr(BIO_F_BIO_ACCEPT, ERR_R_MALLOC_FAILURE);
            BIO_closesocket(ret);
            ret = (int)INVALID_SOCKET;
        } else {
            strcpy(*ip_port, host);
            strcat(*ip_port, ":");
            strcat(*ip_port, port);
        }
        OPENSSL_free(host);
        OPENSSL_free(port);
    }

 end:
    return ret;
}