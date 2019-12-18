#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  excludes; } ;
typedef  TYPE_1__ _BIG5EncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 char* _bcs_skip_ws_len (char const*,size_t*) ; 
 int /*<<< orphan*/  _citrus_BIG5_encoding_module_uninit (TYPE_1__*) ; 
 int /*<<< orphan*/  _citrus_BIG5_fill_rowcol (TYPE_1__*,char*,int,int) ; 
 int _citrus_prop_parse_variable (int /*<<< orphan*/ ,void*,char const*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_hints ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_BIG5_encoding_module_init(_BIG5EncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	const char *s;
	int err;

	memset((void *)ei, 0, sizeof(*ei));
	TAILQ_INIT(&ei->excludes);

	if (lenvar > 0 && var != NULL) {
		s = _bcs_skip_ws_len((const char *)var, &lenvar);
		if (lenvar > 0 && *s != '\0') {
			err = _citrus_prop_parse_variable(
			    root_hints, (void *)ei, s, lenvar);
			if (err == 0)
				return (0);

			_citrus_BIG5_encoding_module_uninit(ei);
			memset((void *)ei, 0, sizeof(*ei));
			TAILQ_INIT(&ei->excludes);
		}
	}

	/* fallback Big5-1984, for backward compatibility. */
	_citrus_BIG5_fill_rowcol(ei, "row", 0xA1, 0xFE);
	_citrus_BIG5_fill_rowcol(ei, "col", 0x40, 0x7E);
	_citrus_BIG5_fill_rowcol(ei, "col", 0xA1, 0xFE);

	return (0);
}