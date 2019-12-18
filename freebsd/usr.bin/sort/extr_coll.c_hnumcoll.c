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
struct key_value {int dummy; } ;

/* Variables and functions */
 int numcoll_impl (struct key_value*,struct key_value*,size_t,int) ; 

__attribute__((used)) static int
hnumcoll(struct key_value *kv1, struct key_value *kv2, size_t offset)
{

	return (numcoll_impl(kv1, kv2, offset, true));
}