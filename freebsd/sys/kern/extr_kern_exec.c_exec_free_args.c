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
struct image_args {int /*<<< orphan*/ * fdp; int /*<<< orphan*/ * fname_buf; int /*<<< orphan*/ * buf; int /*<<< orphan*/  bufkva; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  exec_free_args_kva (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdescfree_remapped (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
exec_free_args(struct image_args *args)
{

	if (args->buf != NULL) {
		exec_free_args_kva(args->bufkva);
		args->buf = NULL;
	}
	if (args->fname_buf != NULL) {
		free(args->fname_buf, M_TEMP);
		args->fname_buf = NULL;
	}
	if (args->fdp != NULL)
		fdescfree_remapped(args->fdp);
}