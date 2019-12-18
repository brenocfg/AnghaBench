#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_peer_info ;
typedef  int /*<<< orphan*/  hx509_cert ;
struct TYPE_3__ {scalar_t__ cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  hx509_cert_free (scalar_t__) ; 
 scalar_t__ hx509_cert_ref (int /*<<< orphan*/ ) ; 

int
hx509_peer_info_set_cert(hx509_peer_info peer,
			 hx509_cert cert)
{
    if (peer->cert)
	hx509_cert_free(peer->cert);
    peer->cert = hx509_cert_ref(cert);
    return 0;
}