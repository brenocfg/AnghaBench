#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int so_domain; int so_type; int so_protocol; } ;
struct TYPE_4__ {TYPE_1__ ar_arg_sockinfo; } ;
struct kaudit_record {TYPE_2__ k_ar; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARG_SET_VALID (struct kaudit_record*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARG_SOCKINFO ; 
 struct kaudit_record* currecord () ; 

void
audit_arg_socket(int sodomain, int sotype, int soprotocol)
{
	struct kaudit_record *ar;

	ar = currecord();
	if (ar == NULL)
		return;

	ar->k_ar.ar_arg_sockinfo.so_domain = sodomain;
	ar->k_ar.ar_arg_sockinfo.so_type = sotype;
	ar->k_ar.ar_arg_sockinfo.so_protocol = soprotocol;
	ARG_SET_VALID(ar, ARG_SOCKINFO);
}