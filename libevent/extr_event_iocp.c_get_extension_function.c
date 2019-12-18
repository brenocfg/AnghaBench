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
typedef  int /*<<< orphan*/  ptr ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  SIO_GET_EXTENSION_FUNCTION_POINTER ; 
 int /*<<< orphan*/  WSAIoctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,void**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
get_extension_function(SOCKET s, const GUID *which_fn)
{
	void *ptr = NULL;
	DWORD bytes=0;
	WSAIoctl(s, SIO_GET_EXTENSION_FUNCTION_POINTER,
	    (GUID*)which_fn, sizeof(*which_fn),
	    &ptr, sizeof(ptr),
	    &bytes, NULL, NULL);

	/* No need to detect errors here: if ptr is set, then we have a good
	   function pointer.  Otherwise, we should behave as if we had no
	   function pointer.
	*/
	return ptr;
}