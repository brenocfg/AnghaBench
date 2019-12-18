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
struct krb5_context {int kc_more_flags; } ;

/* Variables and functions */
 int LOCAL ; 

__attribute__((used)) static __inline int
is_initiator(struct krb5_context *kc)
{
	return (kc->kc_more_flags & LOCAL);
}