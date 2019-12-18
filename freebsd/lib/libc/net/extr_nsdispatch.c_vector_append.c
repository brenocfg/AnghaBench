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

/* Variables and functions */
 unsigned int ELEMSPERCHUNK ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  memmove (void*,void const*,size_t) ; 
 int /*<<< orphan*/  nss_log_simple (int /*<<< orphan*/ ,char*) ; 
 void* reallocarray (void*,unsigned int,size_t) ; 

__attribute__((used)) static void *
vector_append(const void *elem, void *vec, unsigned int *count, size_t esize)
{
	void	*p;

	if ((*count % ELEMSPERCHUNK) == 0) {
		p = reallocarray(vec, *count + ELEMSPERCHUNK, esize);
		if (p == NULL) {
			nss_log_simple(LOG_ERR, "memory allocation failure");
			return (vec);
		}
		vec = p;
	}
	memmove((void *)(((uintptr_t)vec) + (*count * esize)), elem, esize);
	(*count)++;
	return (vec);
}