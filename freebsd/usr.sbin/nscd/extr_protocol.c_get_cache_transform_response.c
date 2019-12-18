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
struct cache_transform_response {int dummy; } ;
struct comm_element {scalar_t__ type; struct cache_transform_response c_transform_response; } ;

/* Variables and functions */
 scalar_t__ CET_TRANSFORM_RESPONSE ; 
 int /*<<< orphan*/  TRACE_IN (struct cache_transform_response* (*) (struct comm_element*)) ; 
 int /*<<< orphan*/  TRACE_OUT (struct cache_transform_response* (*) (struct comm_element*)) ; 
 int /*<<< orphan*/  assert (int) ; 

struct cache_transform_response *
get_cache_transform_response(struct comm_element *element)
{

	TRACE_IN(get_cache_transform_response);
	assert(element->type == CET_TRANSFORM_RESPONSE);
	TRACE_OUT(get_cache_transform_response);
	return (&element->c_transform_response);
}