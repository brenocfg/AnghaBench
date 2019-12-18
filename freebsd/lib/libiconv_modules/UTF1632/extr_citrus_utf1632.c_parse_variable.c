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
struct TYPE_3__ {int preffered_endian; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ _UTF1632EncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  MATCH (int /*<<< orphan*/ ,int) ; 
 int _ENDIAN_BIG ; 
 int _ENDIAN_INTERNAL ; 
 int _ENDIAN_LITTLE ; 
 int _ENDIAN_SWAPPED ; 
 int /*<<< orphan*/  _MODE_FORCE_ENDIAN ; 
 int /*<<< orphan*/  _MODE_UTF32 ; 
 int /*<<< orphan*/  big ; 
 int /*<<< orphan*/  force ; 
 int /*<<< orphan*/  internal ; 
 int /*<<< orphan*/  little ; 
 int /*<<< orphan*/  swapped ; 
 int /*<<< orphan*/  utf32 ; 

__attribute__((used)) static void
parse_variable(_UTF1632EncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	const char *p;

	p = var;
	while (lenvar > 0) {
		switch (*p) {
		case 'B':
		case 'b':
			MATCH(big, ei->preffered_endian = _ENDIAN_BIG);
			break;
		case 'L':
		case 'l':
			MATCH(little, ei->preffered_endian = _ENDIAN_LITTLE);
			break;
		case 'i':
		case 'I':
			MATCH(internal, ei->preffered_endian = _ENDIAN_INTERNAL);
			break;
		case 's':
		case 'S':
			MATCH(swapped, ei->preffered_endian = _ENDIAN_SWAPPED);
			break;
		case 'F':
		case 'f':
			MATCH(force, ei->mode |= _MODE_FORCE_ENDIAN);
			break;
		case 'U':
		case 'u':
			MATCH(utf32, ei->mode |= _MODE_UTF32);
			break;
		}
		p++;
		lenvar--;
	}
}