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
struct dir_ent {struct dir_ent* dirname; } ;

/* Variables and functions */
 struct dir_ent* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 struct dir_ent* TAILQ_NEXT (struct dir_ent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dir_q ; 
 int /*<<< orphan*/  dirs ; 
 int /*<<< orphan*/  free (struct dir_ent*) ; 

__attribute__((used)) static void
free_dir_q(void)
{
	struct dir_ent *d1, *d2;

	d1 = TAILQ_FIRST(&dir_q);
	while (d1 != NULL) {
		d2 = TAILQ_NEXT(d1, dirs);
		free(d1->dirname);
		free(d1);
		d1 = d2;
	}
	TAILQ_INIT(&dir_q);
}