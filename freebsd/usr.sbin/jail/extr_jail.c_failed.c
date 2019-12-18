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
struct cfjail {int /*<<< orphan*/ * queue; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  JF_FAILED ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct cfjail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct cfjail*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ready ; 
 int /*<<< orphan*/  tq ; 

void
failed(struct cfjail *j)
{
	j->flags |= JF_FAILED;
	TAILQ_REMOVE(j->queue, j, tq);
	TAILQ_INSERT_HEAD(&ready, j, tq);
	j->queue = &ready;
}