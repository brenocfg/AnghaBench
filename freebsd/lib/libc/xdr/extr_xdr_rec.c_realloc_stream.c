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
typedef  int ptrdiff_t ;
typedef  int /*<<< orphan*/  bool_t ;
struct TYPE_3__ {int recvsize; char* in_base; int in_finger; char* in_boundry; int in_size; } ;
typedef  TYPE_1__ RECSTREAM ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static bool_t
realloc_stream(RECSTREAM *rstrm, int size)
{
	ptrdiff_t diff;
	char *buf;

	if (size > rstrm->recvsize) {
		buf = realloc(rstrm->in_base, (size_t)size);
		if (buf == NULL)
			return FALSE;
		diff = buf - rstrm->in_base;
		rstrm->in_finger += diff;
		rstrm->in_base = buf;
		rstrm->in_boundry = buf + size;
		rstrm->recvsize = size;
		rstrm->in_size = size;
	}

	return TRUE;
}