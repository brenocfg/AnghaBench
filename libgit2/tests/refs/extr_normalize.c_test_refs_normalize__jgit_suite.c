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
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL ; 
 int /*<<< orphan*/  GIT_REFERENCE_FORMAT_NORMAL ; 
 int GIT_REFNAME_MAX ; 
 int /*<<< orphan*/  ensure_refname_invalid (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ensure_refname_normalized (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  p_snprintf (char*,int,char*,char) ; 

void test_refs_normalize__jgit_suite(void)
{
	/* tests borrowed from JGit */

/* EmptyString */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "/");

/* MustHaveTwoComponents */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_NORMAL, "master");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_NORMAL, "heads/master", "heads/master");

/* ValidHead */
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master", "refs/heads/master");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/pu", "refs/heads/pu");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/z", "refs/heads/z");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/FoO", "refs/heads/FoO");

/* ValidTag */
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/tags/v1.0", "refs/tags/v1.0");

/* NoLockSuffix */
	ensure_refname_invalid(GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master.lock");

/* NoDirectorySuffix */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master/");

/* NoSpace */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/i haz space");

/* NoAsciiControlCharacters */
	{
		char c;
		char buffer[GIT_REFNAME_MAX];
		for (c = '\1'; c < ' '; c++) {
			p_snprintf(buffer, sizeof(buffer), "refs/heads/mast%cer", c);
			ensure_refname_invalid(GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, buffer);
		}
	}

/* NoBareDot */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/.");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/..");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/./master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/../master");

/* NoLeadingOrTrailingDot */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, ".");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/.bar");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/..bar");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/bar.");

/* ContainsDot */
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/m.a.s.t.e.r", "refs/heads/m.a.s.t.e.r");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master..pu");

/* NoMagicRefCharacters */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master^");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/^master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "^refs/heads/master");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master~");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/~master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "~refs/heads/master");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master:");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/:master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, ":refs/heads/master");

/* ShellGlob */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master?");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/?master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "?refs/heads/master");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master[");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/[master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "[refs/heads/master");

	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master*");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/*master");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "*refs/heads/master");

/* ValidSpecialCharacters */
	ensure_refname_normalized
		(GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/!", "refs/heads/!");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/\"", "refs/heads/\"");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/#", "refs/heads/#");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/$", "refs/heads/$");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/%", "refs/heads/%");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/&", "refs/heads/&");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/'", "refs/heads/'");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/(", "refs/heads/(");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/)", "refs/heads/)");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/+", "refs/heads/+");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/,", "refs/heads/,");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/-", "refs/heads/-");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/;", "refs/heads/;");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/<", "refs/heads/<");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/=", "refs/heads/=");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/>", "refs/heads/>");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/@", "refs/heads/@");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/]", "refs/heads/]");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/_", "refs/heads/_");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/`", "refs/heads/`");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/{", "refs/heads/{");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/|", "refs/heads/|");
	ensure_refname_normalized(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/}", "refs/heads/}");

	/*
	 * This is valid on UNIX, but not on Windows
	 * hence we make in invalid due to non-portability
	 */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/\\");

/* UnicodeNames */
	/*
	 * Currently this fails.
	 * ensure_refname_normalized(GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/\u00e5ngstr\u00f6m", "refs/heads/\u00e5ngstr\u00f6m");
	 */

/* RefLogQueryIsValidRef */
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master@{1}");
	ensure_refname_invalid(
		GIT_REFERENCE_FORMAT_ALLOW_ONELEVEL, "refs/heads/master@{1.hour.ago}");
}