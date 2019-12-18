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
typedef  int /*<<< orphan*/  u_int ;
struct intsrc {int /*<<< orphan*/  is_event; } ;

/* Variables and functions */
 int EINVAL ; 
 int intr_event_describe_handler (int /*<<< orphan*/ ,void*,char const*) ; 
 struct intsrc* intr_lookup_source (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intrcnt_updatename (struct intsrc*) ; 

int
intr_describe(u_int vector, void *ih, const char *descr)
{
	struct intsrc *isrc;
	int error;

	isrc = intr_lookup_source(vector);
	if (isrc == NULL)
		return (EINVAL);
	error = intr_event_describe_handler(isrc->is_event, ih, descr);
	if (error)
		return (error);
	intrcnt_updatename(isrc);
	return (0);
}