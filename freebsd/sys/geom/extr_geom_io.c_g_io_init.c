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
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  biozone ; 
 int /*<<< orphan*/  g_bio_run_down ; 
 int /*<<< orphan*/  g_bio_run_up ; 
 int /*<<< orphan*/  g_bioq_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uma_zcreate (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
g_io_init()
{

	g_bioq_init(&g_bio_run_down);
	g_bioq_init(&g_bio_run_up);
	biozone = uma_zcreate("g_bio", sizeof (struct bio),
	    NULL, NULL,
	    NULL, NULL,
	    0, 0);
}