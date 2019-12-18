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
typedef  int /*<<< orphan*/  krb5_error_code ;
typedef  int /*<<< orphan*/  krb5_context ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  RETVAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STRINGMATCH (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  krb5_acl_match_string (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  krb5_errx (int /*<<< orphan*/ ,int,char*) ; 

__attribute__((used)) static void
test_match_string(krb5_context context)
{
    krb5_error_code ret;
    char *s1, *s2;

    ret = krb5_acl_match_string(context, "foo", "s", "foo");
    RETVAL(context, ret, 0, "single s");
    ret = krb5_acl_match_string(context, "foo foo", "s", "foo");
    RETVAL(context, ret, EACCES, "too many strings");
    ret = krb5_acl_match_string(context, "foo bar", "ss", "foo", "bar");
    RETVAL(context, ret, 0, "two strings");
    ret = krb5_acl_match_string(context, "foo  bar", "ss", "foo", "bar");
    RETVAL(context, ret, 0, "two strings double space");
    ret = krb5_acl_match_string(context, "foo \tbar", "ss", "foo", "bar");
    RETVAL(context, ret, 0, "two strings space + tab");
    ret = krb5_acl_match_string(context, "foo", "ss", "foo", "bar");
    RETVAL(context, ret, EACCES, "one string, two format strings");
    ret = krb5_acl_match_string(context, "foo", "ss", "foo", "foo");
    RETVAL(context, ret, EACCES, "one string, two format strings (same)");
    ret = krb5_acl_match_string(context, "foo  \t", "s", "foo");
    RETVAL(context, ret, 0, "ending space");

    ret = krb5_acl_match_string(context, "foo/bar", "f", "foo/bar");
    RETVAL(context, ret, 0, "liternal fnmatch");
    ret = krb5_acl_match_string(context, "foo/bar", "f", "foo/*");
    RETVAL(context, ret, 0, "foo/*");
    ret = krb5_acl_match_string(context, "foo/bar.example.org", "f",
				"foo/*.example.org");
    RETVAL(context, ret, 0, "foo/*.example.org");
    ret = krb5_acl_match_string(context, "foo/bar.example.com", "f",
				"foo/*.example.org");
    RETVAL(context, ret, EACCES, "foo/*.example.com");

    ret = krb5_acl_match_string(context, "foo/bar/baz", "f", "foo/*/baz");
    RETVAL(context, ret, 0, "foo/*/baz");

    ret = krb5_acl_match_string(context, "foo", "r", &s1);
    RETVAL(context, ret, 0, "ret 1");
    STRINGMATCH(context, "ret 1 match", s1, "foo"); free(s1);

    ret = krb5_acl_match_string(context, "foo bar", "rr", &s1, &s2);
    RETVAL(context, ret, 0, "ret 2");
    STRINGMATCH(context, "ret 2 match 1", s1, "foo"); free(s1);
    STRINGMATCH(context, "ret 2 match 2", s2, "bar"); free(s2);

    ret = krb5_acl_match_string(context, "foo bar", "sr", "bar", &s1);
    RETVAL(context, ret, EACCES, "ret mismatch");
    if (s1 != NULL) krb5_errx(context, 1, "s1 not NULL");

    ret = krb5_acl_match_string(context, "foo", "l", "foo");
    RETVAL(context, ret, EINVAL, "unknown letter");
}