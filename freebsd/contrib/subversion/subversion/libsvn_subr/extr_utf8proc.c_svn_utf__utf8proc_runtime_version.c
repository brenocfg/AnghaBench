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

/* Variables and functions */
 int /*<<< orphan*/  SVN_UNUSED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  utf8proc_NFC ; 
 int /*<<< orphan*/  utf8proc_NFD ; 
 int /*<<< orphan*/  utf8proc_NFKC ; 
 int /*<<< orphan*/  utf8proc_NFKD ; 
 int /*<<< orphan*/  utf8proc_category_string ; 
 int /*<<< orphan*/  utf8proc_charwidth ; 
 int /*<<< orphan*/  utf8proc_grapheme_break ; 
 int /*<<< orphan*/  utf8proc_tolower ; 
 int /*<<< orphan*/  utf8proc_totitle ; 
 int /*<<< orphan*/  utf8proc_toupper ; 
 char const* utf8proc_version () ; 

const char *
svn_utf__utf8proc_runtime_version(void)
{
  /* Unused static function warning removal hack. */
  SVN_UNUSED(utf8proc_grapheme_break);
  SVN_UNUSED(utf8proc_tolower);
  SVN_UNUSED(utf8proc_toupper);
#if UTF8PROC_VERSION_MAJOR >= 2
  SVN_UNUSED(utf8proc_totitle);
#endif
  SVN_UNUSED(utf8proc_charwidth);
  SVN_UNUSED(utf8proc_category_string);
  SVN_UNUSED(utf8proc_NFD);
  SVN_UNUSED(utf8proc_NFC);
  SVN_UNUSED(utf8proc_NFKD);
  SVN_UNUSED(utf8proc_NFKC);

  return utf8proc_version();
}