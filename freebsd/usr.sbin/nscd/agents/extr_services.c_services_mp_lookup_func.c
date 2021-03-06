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
struct servent {int dummy; } ;

/* Variables and functions */
 int NS_NOTFOUND ; 
 int NS_SUCCESS ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (char**,size_t*,void*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (char**,size_t*,void*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct servent* getservent () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  services_marshal_func (struct servent*,char*,size_t*) ; 

__attribute__((used)) static int
services_mp_lookup_func(char **buffer, size_t *buffer_size, void *mdata)
{
	struct servent *result;

	TRACE_IN(services_mp_lookup_func);
	result = getservent();
	if (result != NULL) {
		services_marshal_func(result, NULL, buffer_size);
		*buffer = malloc(*buffer_size);
		assert(*buffer != NULL);
		services_marshal_func(result, *buffer, buffer_size);
	}

	TRACE_OUT(services_mp_lookup_func);
	return (result == NULL ? NS_NOTFOUND : NS_SUCCESS);
}