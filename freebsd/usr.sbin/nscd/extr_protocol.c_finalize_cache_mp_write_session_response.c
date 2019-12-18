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
struct cache_mp_write_session_response {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE_IN (void (*) (struct cache_mp_write_session_response*)) ; 
 int /*<<< orphan*/  TRACE_OUT (void (*) (struct cache_mp_write_session_response*)) ; 

void
finalize_cache_mp_write_session_response(
	struct cache_mp_write_session_response *mp_ws_response)
{

	TRACE_IN(finalize_cache_mp_write_session_response);
	TRACE_OUT(finalize_cache_mp_write_session_response);
}