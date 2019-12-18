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
struct update_info_ctx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_info_ref ; 
 int for_each_ref (int /*<<< orphan*/ ,struct update_info_ctx*) ; 

__attribute__((used)) static int generate_info_refs(struct update_info_ctx *uic)
{
	return for_each_ref(add_info_ref, uic);
}