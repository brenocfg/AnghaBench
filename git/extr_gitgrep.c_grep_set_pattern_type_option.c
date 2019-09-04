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
struct grep_opt {int extended_regexp_option; int fixed; int pcre1; } ;
typedef  enum grep_pattern_type { ____Placeholder_grep_pattern_type } grep_pattern_type ;

/* Variables and functions */
#define  GREP_PATTERN_TYPE_BRE 132 
#define  GREP_PATTERN_TYPE_ERE 131 
#define  GREP_PATTERN_TYPE_FIXED 130 
#define  GREP_PATTERN_TYPE_PCRE 129 
#define  GREP_PATTERN_TYPE_UNSPECIFIED 128 

__attribute__((used)) static void grep_set_pattern_type_option(enum grep_pattern_type pattern_type, struct grep_opt *opt)
{
	/*
	 * When committing to the pattern type by setting the relevant
	 * fields in grep_opt it's generally not necessary to zero out
	 * the fields we're not choosing, since they won't have been
	 * set by anything. The extended_regexp_option field is the
	 * only exception to this.
	 *
	 * This is because in the process of parsing grep.patternType
	 * & grep.extendedRegexp we set opt->pattern_type_option and
	 * opt->extended_regexp_option, respectively. We then
	 * internally use opt->extended_regexp_option to see if we're
	 * compiling an ERE. It must be unset if that's not actually
	 * the case.
	 */
	if (pattern_type != GREP_PATTERN_TYPE_ERE &&
	    opt->extended_regexp_option)
		opt->extended_regexp_option = 0;

	switch (pattern_type) {
	case GREP_PATTERN_TYPE_UNSPECIFIED:
		/* fall through */

	case GREP_PATTERN_TYPE_BRE:
		break;

	case GREP_PATTERN_TYPE_ERE:
		opt->extended_regexp_option = 1;
		break;

	case GREP_PATTERN_TYPE_FIXED:
		opt->fixed = 1;
		break;

	case GREP_PATTERN_TYPE_PCRE:
#ifdef USE_LIBPCRE2
		opt->pcre2 = 1;
#else
		/*
		 * It's important that pcre1 always be assigned to
		 * even when there's no USE_LIBPCRE* defined. We still
		 * call the PCRE stub function, it just dies with
		 * "cannot use Perl-compatible regexes[...]".
		 */
		opt->pcre1 = 1;
#endif
		break;
	}
}