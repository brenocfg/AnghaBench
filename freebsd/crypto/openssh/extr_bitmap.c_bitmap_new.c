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
struct bitmap {int len; scalar_t__ top; int /*<<< orphan*/ * d; } ;

/* Variables and functions */
 int BITMAP_BYTES ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  free (struct bitmap*) ; 

struct bitmap *
bitmap_new(void)
{
	struct bitmap *ret;

	if ((ret = calloc(1, sizeof(*ret))) == NULL)
		return NULL;
	if ((ret->d = calloc(1, BITMAP_BYTES)) == NULL) {
		free(ret);
		return NULL;
	}
	ret->len = 1;
	ret->top = 0;
	return ret;
}