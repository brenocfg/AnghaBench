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
struct ttm_buffer_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_TRANSF_OBJ ; 
 int /*<<< orphan*/  free (struct ttm_buffer_object*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_transfered_destroy(struct ttm_buffer_object *bo)
{
	free(bo, M_TTM_TRANSF_OBJ);
}