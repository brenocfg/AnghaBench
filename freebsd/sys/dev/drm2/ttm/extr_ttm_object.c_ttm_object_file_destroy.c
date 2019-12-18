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
struct ttm_object_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TTM_OBJ_FILE ; 
 int /*<<< orphan*/  free (struct ttm_object_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ttm_object_file_destroy(struct ttm_object_file *tfile)
{

	free(tfile, M_TTM_OBJ_FILE);
}