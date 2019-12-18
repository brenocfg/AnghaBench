#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _memstream {int dummy; } ;
struct TYPE_4__ {int boolean; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ _citrus_prop_object_t ;

/* Variables and functions */
 int EINVAL ; 
 char _bcs_tolower (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _memstream_getc (struct _memstream*) ; 
 int /*<<< orphan*/  _memstream_skip_ws (struct _memstream*) ; 

__attribute__((used)) static int
_citrus_prop_read_bool(struct _memstream * __restrict ms,
    _citrus_prop_object_t * __restrict obj)
{

	_memstream_skip_ws(ms);
	switch (_bcs_tolower(_memstream_getc(ms))) {
	case 't':
		if (_bcs_tolower(_memstream_getc(ms)) == 'r' &&
		    _bcs_tolower(_memstream_getc(ms)) == 'u' &&
		    _bcs_tolower(_memstream_getc(ms)) == 'e') {
			obj->u.boolean = true;
			return (0);
		}
		break;
	case 'f':
		if (_bcs_tolower(_memstream_getc(ms)) == 'a' &&
		    _bcs_tolower(_memstream_getc(ms)) == 'l' &&
		    _bcs_tolower(_memstream_getc(ms)) == 's' &&
		    _bcs_tolower(_memstream_getc(ms)) == 'e') {
			obj->u.boolean = false;
			return (0);
		}
	}
	return (EINVAL);
}