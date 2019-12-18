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
typedef  int /*<<< orphan*/  _HZEncodingInfo ;

/* Variables and functions */
 int /*<<< orphan*/  E0SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  E1SET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _citrus_HZ_encoding_module_uninit (int /*<<< orphan*/ *) ; 
 int _citrus_prop_parse_variable (int /*<<< orphan*/ ,void*,void const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  root_hints ; 

__attribute__((used)) static int
_citrus_HZ_encoding_module_init(_HZEncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{
	int errnum;

	memset(ei, 0, sizeof(*ei));
	TAILQ_INIT(E0SET(ei));
	TAILQ_INIT(E1SET(ei));
	errnum = _citrus_prop_parse_variable(
	    root_hints, (void *)ei, var, lenvar);
	if (errnum != 0)
		_citrus_HZ_encoding_module_uninit(ei);
	return (errnum);
}