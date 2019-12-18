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
struct attr_check_item {char* value; } ;

/* Variables and functions */
 scalar_t__ ATTR_FALSE (char const*) ; 
 scalar_t__ ATTR_TRUE (char const*) ; 
 scalar_t__ ATTR_UNSET (char const*) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  default_encoding ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ) ; 
 scalar_t__ same_encoding (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static const char *git_path_check_encoding(struct attr_check_item *check)
{
	const char *value = check->value;

	if (ATTR_UNSET(value) || !strlen(value))
		return NULL;

	if (ATTR_TRUE(value) || ATTR_FALSE(value)) {
		die(_("true/false are no valid working-tree-encodings"));
	}

	/* Don't encode to the default encoding */
	if (same_encoding(value, default_encoding))
		return NULL;

	return value;
}