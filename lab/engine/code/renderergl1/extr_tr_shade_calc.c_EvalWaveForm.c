#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  frequency; int /*<<< orphan*/  phase; int /*<<< orphan*/  amplitude; int /*<<< orphan*/  base; int /*<<< orphan*/  func; } ;
typedef  TYPE_1__ waveForm_t ;

/* Variables and functions */
 float* TableForFunc (int /*<<< orphan*/ ) ; 
 float WAVEVALUE (float*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static float EvalWaveForm( const waveForm_t *wf ) 
{
	float	*table;

	table = TableForFunc( wf->func );

	return WAVEVALUE( table, wf->base, wf->amplitude, wf->phase, wf->frequency );
}