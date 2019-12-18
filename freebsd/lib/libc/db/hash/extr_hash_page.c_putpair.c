#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct TYPE_4__ {int size; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ DBT ;

/* Variables and functions */
 int OFFSET (int*) ; 
 int /*<<< orphan*/  memmove (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
putpair(char *p, const DBT *key, const DBT *val)
{
	u_int16_t *bp, n, off;

	bp = (u_int16_t *)p;

	/* Enter the key first. */
	n = bp[0];

	off = OFFSET(bp) - key->size;
	memmove(p + off, key->data, key->size);
	bp[++n] = off;

	/* Now the data. */
	off -= val->size;
	memmove(p + off, val->data, val->size);
	bp[++n] = off;

	/* Adjust page info. */
	bp[0] = n;
	bp[n + 1] = off - ((n + 3) * sizeof(u_int16_t));
	bp[n + 2] = off;
}