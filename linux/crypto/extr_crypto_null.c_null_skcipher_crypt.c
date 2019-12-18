#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ addr; } ;
struct TYPE_7__ {TYPE_4__ virt; } ;
struct TYPE_5__ {scalar_t__ addr; } ;
struct TYPE_6__ {TYPE_1__ virt; } ;
struct skcipher_walk {scalar_t__ nbytes; TYPE_3__ src; TYPE_2__ dst; } ;
struct skcipher_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 
 int skcipher_walk_done (struct skcipher_walk*,int /*<<< orphan*/ ) ; 
 int skcipher_walk_virt (struct skcipher_walk*,struct skcipher_request*,int) ; 

__attribute__((used)) static int null_skcipher_crypt(struct skcipher_request *req)
{
	struct skcipher_walk walk;
	int err;

	err = skcipher_walk_virt(&walk, req, false);

	while (walk.nbytes) {
		if (walk.src.virt.addr != walk.dst.virt.addr)
			memcpy(walk.dst.virt.addr, walk.src.virt.addr,
			       walk.nbytes);
		err = skcipher_walk_done(&walk, 0);
	}

	return err;
}