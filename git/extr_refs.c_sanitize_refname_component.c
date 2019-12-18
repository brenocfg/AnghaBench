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
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,char const*) ; 
 int /*<<< orphan*/  REFNAME_ALLOW_ONELEVEL ; 
 scalar_t__ check_or_sanitize_refname (char const*,int /*<<< orphan*/ ,struct strbuf*) ; 

void sanitize_refname_component(const char *refname, struct strbuf *out)
{
	if (check_or_sanitize_refname(refname, REFNAME_ALLOW_ONELEVEL, out))
		BUG("sanitizing refname '%s' check returned error", refname);
}