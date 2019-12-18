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
struct gctl_req {int /*<<< orphan*/  nerror; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  copyin (void*,void*,size_t) ; 
 int /*<<< orphan*/  g_free (void*) ; 
 void* g_malloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
geom_alloc_copyin(struct gctl_req *req, void *uaddr, size_t len)
{
	void *ptr;

	ptr = g_malloc(len, M_WAITOK);
	req->nerror = copyin(uaddr, ptr, len);
	if (!req->nerror)
		return (ptr);
	g_free(ptr);
	return (NULL);
}