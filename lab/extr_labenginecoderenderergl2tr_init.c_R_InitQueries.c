#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  occlusionQuery; } ;
struct TYPE_5__ {scalar_t__ integer; } ;
struct TYPE_4__ {int /*<<< orphan*/  sunFlareQuery; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_LEN (int /*<<< orphan*/ ) ; 
 TYPE_3__ glRefConfig ; 
 int /*<<< orphan*/  qglGenQueries (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* r_drawSunRays ; 
 TYPE_1__ tr ; 

void R_InitQueries(void)
{
	if (!glRefConfig.occlusionQuery)
		return;

	if (r_drawSunRays->integer)
		qglGenQueries(ARRAY_LEN(tr.sunFlareQuery), tr.sunFlareQuery);
}