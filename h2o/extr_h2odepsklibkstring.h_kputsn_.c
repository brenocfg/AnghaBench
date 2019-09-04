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
struct TYPE_3__ {scalar_t__ l; scalar_t__ m; char* s; } ;
typedef  TYPE_1__ kstring_t ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  kroundup32 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 scalar_t__ realloc (char*,scalar_t__) ; 

__attribute__((used)) static inline int kputsn_(const void *p, int l, kstring_t *s)
{
	if (s->l + l > s->m) {
		char *tmp;
		s->m = s->l + l;
		kroundup32(s->m);
		if ((tmp = (char*)realloc(s->s, s->m)))
			s->s = tmp;
		else
			return EOF;
	}
	memcpy(s->s + s->l, p, l);
	s->l += l;
	return l;
}