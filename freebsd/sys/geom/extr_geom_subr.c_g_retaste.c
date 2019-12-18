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
struct g_hh00 {int post; int error; struct g_class* mp; } ;
struct g_class {int /*<<< orphan*/ * taste; } ;

/* Variables and functions */
 int EINVAL ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 scalar_t__ cold ; 
 int /*<<< orphan*/  g_free (struct g_hh00*) ; 
 struct g_hh00* g_malloc (int,int) ; 
 int g_post_event (int /*<<< orphan*/ ,struct g_hh00*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_retaste_event ; 
 int g_waitfor_event (int /*<<< orphan*/ ,struct g_hh00*,int,int /*<<< orphan*/ *) ; 

int
g_retaste(struct g_class *mp)
{
	struct g_hh00 *hh;
	int error;

	if (mp->taste == NULL)
		return (EINVAL);

	hh = g_malloc(sizeof *hh, M_WAITOK | M_ZERO);
	hh->mp = mp;

	if (cold) {
		hh->post = 1;
		error = g_post_event(g_retaste_event, hh, M_WAITOK, NULL);
	} else {
		error = g_waitfor_event(g_retaste_event, hh, M_WAITOK, NULL);
		if (error == 0)
			error = hh->error;
		g_free(hh);
	}

	return (error);
}