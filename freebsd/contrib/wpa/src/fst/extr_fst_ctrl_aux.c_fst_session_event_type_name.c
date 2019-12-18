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
typedef  enum fst_event_type { ____Placeholder_fst_event_type } fst_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 char const* fst_get_str_name (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  session_event_names ; 

const char * fst_session_event_type_name(enum fst_event_type event)
{
	return fst_get_str_name(event, session_event_names,
				ARRAY_SIZE(session_event_names));
}