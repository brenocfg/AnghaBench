#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  connect_family; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ BIO_CONNECT ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CONN_S_BEFORE ; 
 int /*<<< orphan*/  BIO_FAMILY_IPANY ; 
 int /*<<< orphan*/  BIO_F_BIO_CONNECT_NEW ; 
 int /*<<< orphan*/  BIOerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

BIO_CONNECT *BIO_CONNECT_new(void)
{
    BIO_CONNECT *ret;

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        BIOerr(BIO_F_BIO_CONNECT_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }
    ret->state = BIO_CONN_S_BEFORE;
    ret->connect_family = BIO_FAMILY_IPANY;
    return ret;
}