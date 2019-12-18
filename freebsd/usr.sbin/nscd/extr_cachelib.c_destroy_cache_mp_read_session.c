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
struct cache_mp_read_session_ {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_mp_read_session_*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_mp_read_session_*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct cache_mp_read_session_*) ; 

__attribute__((used)) static void
destroy_cache_mp_read_session(struct cache_mp_read_session_ *rs)
{

	TRACE_IN(destroy_cache_mp_read_session);
	assert(rs != NULL);
	free(rs);
	TRACE_OUT(destroy_cache_mp_read_session);
}