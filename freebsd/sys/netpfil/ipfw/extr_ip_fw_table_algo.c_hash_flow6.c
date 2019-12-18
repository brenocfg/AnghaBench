#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_8__ {int dport; int sport; } ;
struct TYPE_6__ {int* __u6_addr32; } ;
struct TYPE_7__ {TYPE_1__ __u6_addr; } ;
struct TYPE_9__ {int* __u6_addr32; } ;
struct TYPE_10__ {TYPE_4__ __u6_addr; } ;
struct fhashentry6 {TYPE_3__ e; TYPE_2__ sip6; TYPE_5__ dip6; } ;

/* Variables and functions */

__attribute__((used)) static __inline uint32_t
hash_flow6(struct fhashentry6 *f, int hsize)
{
	uint32_t i;

	i = (f->dip6.__u6_addr.__u6_addr32[2]) ^
	    (f->dip6.__u6_addr.__u6_addr32[3]) ^
	    (f->sip6.__u6_addr.__u6_addr32[2]) ^
	    (f->sip6.__u6_addr.__u6_addr32[3]) ^
	    (f->e.dport) ^ (f->e.sport);

	return (i % (hsize - 1));
}