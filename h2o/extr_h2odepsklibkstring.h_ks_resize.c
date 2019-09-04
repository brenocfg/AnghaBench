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
struct TYPE_3__ {size_t m; char* s; } ;
typedef  TYPE_1__ kstring_t ;

/* Variables and functions */
 int /*<<< orphan*/  kroundup32 (size_t) ; 
 scalar_t__ realloc (char*,size_t) ; 

__attribute__((used)) static inline int ks_resize(kstring_t *s, size_t size)
{
	if (s->m < size) {
		char *tmp;
		s->m = size;
		kroundup32(s->m);
		if ((tmp = (char*)realloc(s->s, s->m)))
			s->s = tmp;
		else
			return -1;
	}
	return 0;
}