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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int /*<<< orphan*/  trace_t ;

/* Variables and functions */
 int /*<<< orphan*/  G_TRACE ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int /*<<< orphan*/  const,int,int) ; 

void trap_Trace( trace_t *results, const vec3_t start, const vec3_t mins, const vec3_t maxs, const vec3_t end, int passEntityNum, int contentmask ) {
	syscall( G_TRACE, results, start, mins, maxs, end, passEntityNum, contentmask );
}