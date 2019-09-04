#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; char* ptr; } ;
typedef  TYPE_3__ xrecord_t ;
struct TYPE_7__ {TYPE_3__** recs; } ;
struct TYPE_6__ {TYPE_3__** recs; } ;
struct TYPE_9__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_4__ xdfenv_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static int xdl_recs_copy_0(int use_orig, xdfenv_t *xe, int i, int count, int needs_cr, int add_nl, char *dest)
{
	xrecord_t **recs;
	int size = 0;

	recs = (use_orig ? xe->xdf1.recs : xe->xdf2.recs) + i;

	if (count < 1)
		return 0;

	for (i = 0; i < count; size += recs[i++]->size)
		if (dest)
			memcpy(dest + size, recs[i]->ptr, recs[i]->size);
	if (add_nl) {
		i = recs[count - 1]->size;
		if (i == 0 || recs[count - 1]->ptr[i - 1] != '\n') {
			if (needs_cr) {
				if (dest)
					dest[size] = '\r';
				size++;
			}

			if (dest)
				dest[size] = '\n';
			size++;
		}
	}
	return size;
}