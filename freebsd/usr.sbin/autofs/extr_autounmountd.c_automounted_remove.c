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
struct automounted_fs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct automounted_fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_next ; 
 int /*<<< orphan*/  automounted ; 
 int /*<<< orphan*/  free (struct automounted_fs*) ; 

__attribute__((used)) static void
automounted_remove(struct automounted_fs *af)
{

	TAILQ_REMOVE(&automounted, af, af_next);
	free(af);
}