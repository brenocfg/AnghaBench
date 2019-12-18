#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct dtoa_context {TYPE_1__** freelist; } ;
struct TYPE_3__ {size_t k; struct TYPE_3__* next; } ;
typedef  TYPE_1__ Bigint ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (void*) ; 
 size_t Kmax ; 
 int /*<<< orphan*/  free (void*) ; 

__attribute__((used)) static void
Bfree
 (struct dtoa_context* C, Bigint *v)
{
	if (v) {
		if (v->k > Kmax)
#ifdef FREE
			FREE((void*)v);
#else
			free((void*)v);
#endif
		else {
			v->next = C->freelist[v->k];
			C->freelist[v->k] = v;
			}
		}
	}