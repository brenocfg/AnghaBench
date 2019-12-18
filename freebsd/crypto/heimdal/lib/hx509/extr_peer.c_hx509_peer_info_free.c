#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* hx509_peer_info ;
struct TYPE_6__ {scalar_t__ cert; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  free_cms_alg (TYPE_1__*) ; 
 int /*<<< orphan*/  hx509_cert_free (scalar_t__) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void
hx509_peer_info_free(hx509_peer_info peer)
{
    if (peer == NULL)
	return;
    if (peer->cert)
	hx509_cert_free(peer->cert);
    free_cms_alg(peer);
    memset(peer, 0, sizeof(*peer));
    free(peer);
}