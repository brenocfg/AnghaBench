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
typedef  enum rfc2047_type { ____Placeholder_rfc2047_type } rfc2047_type ;

/* Variables and functions */
 int RFC2047_ADDRESS ; 
 scalar_t__ isalnum (char) ; 
 int /*<<< orphan*/  isprint (char) ; 
 scalar_t__ isspace (char) ; 
 scalar_t__ non_ascii (char) ; 

__attribute__((used)) static int is_rfc2047_special(char ch, enum rfc2047_type type)
{
	/*
	 * rfc2047, section 4.2:
	 *
	 *    8-bit values which correspond to printable ASCII characters other
	 *    than "=", "?", and "_" (underscore), MAY be represented as those
	 *    characters.  (But see section 5 for restrictions.)  In
	 *    particular, SPACE and TAB MUST NOT be represented as themselves
	 *    within encoded words.
	 */

	/*
	 * rule out non-ASCII characters and non-printable characters (the
	 * non-ASCII check should be redundant as isprint() is not localized
	 * and only knows about ASCII, but be defensive about that)
	 */
	if (non_ascii(ch) || !isprint(ch))
		return 1;

	/*
	 * rule out special printable characters (' ' should be the only
	 * whitespace character considered printable, but be defensive and use
	 * isspace())
	 */
	if (isspace(ch) || ch == '=' || ch == '?' || ch == '_')
		return 1;

	/*
	 * rfc2047, section 5.3:
	 *
	 *    As a replacement for a 'word' entity within a 'phrase', for example,
	 *    one that precedes an address in a From, To, or Cc header.  The ABNF
	 *    definition for 'phrase' from RFC 822 thus becomes:
	 *
	 *    phrase = 1*( encoded-word / word )
	 *
	 *    In this case the set of characters that may be used in a "Q"-encoded
	 *    'encoded-word' is restricted to: <upper and lower case ASCII
	 *    letters, decimal digits, "!", "*", "+", "-", "/", "=", and "_"
	 *    (underscore, ASCII 95.)>.  An 'encoded-word' that appears within a
	 *    'phrase' MUST be separated from any adjacent 'word', 'text' or
	 *    'special' by 'linear-white-space'.
	 */

	if (type != RFC2047_ADDRESS)
		return 0;

	/* '=' and '_' are special cases and have been checked above */
	return !(isalnum(ch) || ch == '!' || ch == '*' || ch == '+' || ch == '-' || ch == '/');
}