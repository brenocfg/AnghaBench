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
typedef  int /*<<< orphan*/  krb5_storage ;
typedef  int /*<<< orphan*/  krb5_socket_t ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcontext ; 
 int /*<<< orphan*/ * krb5_storage_from_fd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_stream (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ *) ; 

int
handle_mit(krb5_context contextp, void *buf, size_t len, krb5_socket_t sock)
{
    krb5_storage *sp;

    dcontext = contextp;

    sp = krb5_storage_from_fd(sock);
    INSIST(sp != NULL);

    process_stream(contextp, buf, len, sp);

    return 0;
}