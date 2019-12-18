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
typedef  int /*<<< orphan*/  _EUCEncodingInfo ;

/* Variables and functions */
 int _citrus_EUC_parse_variable (int /*<<< orphan*/ *,void const*,size_t) ; 

__attribute__((used)) static int
/*ARGSUSED*/
_citrus_EUC_encoding_module_init(_EUCEncodingInfo * __restrict ei,
    const void * __restrict var, size_t lenvar)
{

	return (_citrus_EUC_parse_variable(ei, var, lenvar));
}