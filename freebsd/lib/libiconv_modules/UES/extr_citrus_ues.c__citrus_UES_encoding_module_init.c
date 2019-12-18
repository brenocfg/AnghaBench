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
struct TYPE_3__ {int mode; int mb_cur_max; } ;
typedef  TYPE_1__ _UESEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  C99 ; 
 int /*<<< orphan*/  MATCH (int /*<<< orphan*/ ,int) ; 
 int MODE_C99 ; 
 int _bcs_toupper (char const) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_UES_encoding_module_init(_UESEncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	const char *p;

	p = var;
	memset((void *)ei, 0, sizeof(*ei));
	while (lenvar > 0) {
		switch (_bcs_toupper(*p)) {
		case 'C':
			MATCH(C99, ei->mode |= MODE_C99);
			break;
		}
		++p;
		--lenvar;
	}
	ei->mb_cur_max = (ei->mode & MODE_C99) ? 10 : 12;

	return (0);
}