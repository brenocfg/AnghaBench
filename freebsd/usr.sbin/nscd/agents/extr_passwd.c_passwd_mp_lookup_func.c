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
struct passwd {int dummy; } ;

/* Variables and functions */
 int NS_NOTFOUND ; 
 int NS_SUCCESS ; 
 int /*<<< orphan*/  TRACE_IN (int (*) (char**,size_t*,void*)) ; 
 int /*<<< orphan*/  TRACE_OUT (int (*) (char**,size_t*,void*)) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 struct passwd* getpwent () ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  passwd_marshal_func (struct passwd*,char*,size_t*) ; 

__attribute__((used)) static int
passwd_mp_lookup_func(char **buffer, size_t *buffer_size, void *mdata)
{
	struct passwd	*result;

	TRACE_IN(passwd_mp_lookup_func);
	result = getpwent();
	if (result != NULL) {
		passwd_marshal_func(result, NULL, buffer_size);
		*buffer = malloc(*buffer_size);
		assert(*buffer != NULL);
		passwd_marshal_func(result, *buffer, buffer_size);
	}

	TRACE_OUT(passwd_mp_lookup_func);
	return (result == NULL ? NS_NOTFOUND : NS_SUCCESS);
}