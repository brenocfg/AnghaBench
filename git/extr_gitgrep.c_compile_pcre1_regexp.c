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
struct grep_pat {int dummy; } ;
struct grep_opt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 

__attribute__((used)) static void compile_pcre1_regexp(struct grep_pat *p, const struct grep_opt *opt)
{
	die("cannot use Perl-compatible regexes when not compiled with USE_LIBPCRE");
}