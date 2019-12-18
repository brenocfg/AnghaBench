#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned int size; } ;
struct drbd_peer_request {TYPE_1__ i; } ;
struct crypto_shash {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drbd_csum_ee (struct crypto_shash*,struct drbd_peer_request*,void*) ; 

__attribute__((used)) static void drbd_csum_ee_size(struct crypto_shash *h,
			      struct drbd_peer_request *r, void *d,
			      unsigned int payload_size)
{
	unsigned int tmp = r->i.size;
	r->i.size = payload_size;
	drbd_csum_ee(h, r, d);
	r->i.size = tmp;
}