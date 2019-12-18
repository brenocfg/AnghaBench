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
struct object_id {int dummy; } ;

/* Variables and functions */
 scalar_t__ check_and_freshen_local (struct object_id const*,int) ; 
 scalar_t__ check_and_freshen_nonlocal (struct object_id const*,int) ; 

__attribute__((used)) static int check_and_freshen(const struct object_id *oid, int freshen)
{
	return check_and_freshen_local(oid, freshen) ||
	       check_and_freshen_nonlocal(oid, freshen);
}