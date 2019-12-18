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
typedef  int /*<<< orphan*/  uint8_t ;
struct t4_tracer {int enabled; scalar_t__ valid; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHELSIO_T4_SET_TRACER ; 
 int doit (int /*<<< orphan*/ ,struct t4_tracer*) ; 

__attribute__((used)) static int
tracer_onoff(uint8_t idx, int enabled)
{
	struct t4_tracer t;

	t.idx = idx;
	t.enabled = enabled;
	t.valid = 0;

	return doit(CHELSIO_T4_SET_TRACER, &t);
}