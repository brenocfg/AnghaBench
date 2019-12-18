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
struct g_classifier_hook {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_classifier_hook*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_bio_run_down ; 
 int /*<<< orphan*/  g_bioq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_bioq_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_classifier_tailq ; 
 int /*<<< orphan*/  link ; 

int
g_register_classifier(struct g_classifier_hook *hook)
{

	g_bioq_lock(&g_bio_run_down);
	TAILQ_INSERT_TAIL(&g_classifier_tailq, hook, link);
	g_bioq_unlock(&g_bio_run_down);

	return (0);
}