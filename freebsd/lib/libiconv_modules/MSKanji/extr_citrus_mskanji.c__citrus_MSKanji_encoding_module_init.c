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
struct TYPE_3__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ _MSKanjiEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  JIS2004 ; 
 int /*<<< orphan*/  MATCH (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MODE_JIS2004 ; 
 int _bcs_toupper (char const) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_MSKanji_encoding_module_init(_MSKanjiEncodingInfo *  __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	const char *p;

	p = var;
	memset((void *)ei, 0, sizeof(*ei));
	while (lenvar > 0) {
		switch (_bcs_toupper(*p)) {
		case 'J':
			MATCH(JIS2004, ei->mode |= MODE_JIS2004);
			break;
		}
		++p;
		--lenvar;
	}

	return (0);
}