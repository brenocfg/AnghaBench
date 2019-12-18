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
struct TYPE_5__ {int /*<<< orphan*/  num; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_clear_retry_flags (TYPE_1__*) ; 
 int /*<<< orphan*/  BIO_set_retry_read (TYPE_1__*) ; 
 scalar_t__ BIO_sock_should_retry (int) ; 
 int /*<<< orphan*/  clear_socket_error () ; 
 int readsocket (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int sock_read(BIO *b, char *out, int outl)
{
    int ret = 0;

    if (out != NULL) {
        clear_socket_error();
        ret = readsocket(b->num, out, outl);
        BIO_clear_retry_flags(b);
        if (ret <= 0) {
            if (BIO_sock_should_retry(ret))
                BIO_set_retry_read(b);
        }
    }
    return ret;
}