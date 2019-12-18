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
struct memory_type {int dummy; } ;

/* Variables and functions */
 struct memory_type* LIST_NEXT (struct memory_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_list ; 

struct memory_type *
memstat_mtl_next(struct memory_type *mtp)
{

	return (LIST_NEXT(mtp, mt_list));
}