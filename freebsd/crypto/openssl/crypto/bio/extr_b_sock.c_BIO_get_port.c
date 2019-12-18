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
typedef  int /*<<< orphan*/  BIO_ADDRINFO ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  BIO_ADDRINFO_address (int /*<<< orphan*/ *) ; 
 scalar_t__ BIO_ADDRINFO_family (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDRINFO_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIO_ADDR_rawport (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_F_BIO_GET_PORT ; 
 int /*<<< orphan*/  BIO_LOOKUP_CLIENT ; 
 int /*<<< orphan*/  BIO_R_ADDRINFO_ADDR_IS_NOT_AF_INET ; 
 int /*<<< orphan*/  BIO_R_NO_PORT_DEFINED ; 
 scalar_t__ BIO_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int BIO_sock_init () ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_add_error_data (int,char*,char const*) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 unsigned short ntohs (int /*<<< orphan*/ ) ; 

int BIO_get_port(const char *str, unsigned short *port_ptr)
{
    BIO_ADDRINFO *res = NULL;
    int ret = 0;

    if (str == NULL) {
        BIOerr(BIO_F_BIO_GET_PORT, BIO_R_NO_PORT_DEFINED);
        return 0;
    }

    if (BIO_sock_init() != 1)
        return 0;               /* don't generate another error code here */

    if (BIO_lookup(NULL, str, BIO_LOOKUP_CLIENT, AF_INET, SOCK_STREAM, &res)) {
        if (BIO_ADDRINFO_family(res) != AF_INET) {
            BIOerr(BIO_F_BIO_GET_PORT,
                   BIO_R_ADDRINFO_ADDR_IS_NOT_AF_INET);
        } else {
            *port_ptr = ntohs(BIO_ADDR_rawport(BIO_ADDRINFO_address(res)));
            ret = 1;
        }
        BIO_ADDRINFO_free(res);
    } else {
        ERR_add_error_data(2, "host=", str);
    }

    return ret;
}