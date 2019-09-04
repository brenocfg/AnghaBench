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
struct object {int dummy; } ;
struct fsck_options {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*,int) ; 
#define  FSCK_ERROR 129 
#define  FSCK_WARN 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  describe_object (struct object*) ; 
 int /*<<< orphan*/  fprintf_ln (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  printable_type (struct object*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int fsck_error_func(struct fsck_options *o,
	struct object *obj, int type, const char *message)
{
	switch (type) {
	case FSCK_WARN:
		/* TRANSLATORS: e.g. warning in tree 01bfda: <more explanation> */
		fprintf_ln(stderr, _("warning in %s %s: %s"),
			   printable_type(obj), describe_object(obj), message);
		return 0;
	case FSCK_ERROR:
		/* TRANSLATORS: e.g. error in tree 01bfda: <more explanation> */
		fprintf_ln(stderr, _("error in %s %s: %s"),
			   printable_type(obj), describe_object(obj), message);
		return 1;
	default:
		BUG("%d (FSCK_IGNORE?) should never trigger this callback", type);
	}
}