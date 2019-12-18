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
typedef  size_t u_int ;
struct TYPE_2__ {size_t snp_proto; char const* snp_name; } ;

/* Variables and functions */
 TYPE_1__* proto_array ; 
 size_t proto_array_len ; 

__attribute__((used)) static const char *
netisr_proto2name(u_int proto)
{
	u_int i;

	for (i = 0; i < proto_array_len; i++) {
		if (proto_array[i].snp_proto == proto)
			return (proto_array[i].snp_name);
	}
	return ("unknown");
}