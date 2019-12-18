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
struct archive_string_conv {int flag; char const* to_charset; char const* from_charset; } ;

/* Variables and functions */
 int SCONV_TO_CHARSET ; 

const char *
archive_string_conversion_charset_name(struct archive_string_conv *sc)
{
	if (sc->flag & SCONV_TO_CHARSET)
		return (sc->to_charset);
	else
		return (sc->from_charset);
}