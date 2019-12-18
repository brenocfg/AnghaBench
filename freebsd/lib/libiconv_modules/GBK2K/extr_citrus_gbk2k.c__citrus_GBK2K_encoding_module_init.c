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
struct TYPE_3__ {int mb_cur_max; } ;
typedef  TYPE_1__ _GBK2KEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MATCH (char*,int) ; 
 int _bcs_tolower (char const) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_GBK2K_encoding_module_init(_GBK2KEncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	const char *p;

	p = var;
	memset((void *)ei, 0, sizeof(*ei));
	ei->mb_cur_max = 4;
	while (lenvar > 0) {
		switch (_bcs_tolower(*p)) {
		case '2':
			MATCH("2byte", ei->mb_cur_max = 2);
			break;
		}
		p++;
		lenvar--;
	}

	return (0);
}