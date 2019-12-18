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
typedef  void dn_id ;

/* Variables and functions */
 void* O_NEXT (void*,int) ; 
 int /*<<< orphan*/  oid_fill (void*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
o_next(struct dn_id **o, int len, int type)
{
	struct dn_id *ret = *o;
	oid_fill(ret, len, type, 0);
	*o = O_NEXT(*o, len);
	return ret;
}