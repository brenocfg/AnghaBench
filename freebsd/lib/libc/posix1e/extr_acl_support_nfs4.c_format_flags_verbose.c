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
typedef  int /*<<< orphan*/  uint32_t ;
struct flagnames_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 char* format_flag (int /*<<< orphan*/ *,struct flagnames_struct const*) ; 
 scalar_t__ snprintf (char*,size_t,char*,char const*) ; 

__attribute__((used)) static int
format_flags_verbose(char *str, size_t size, uint32_t var,
    const struct flagnames_struct *flags)
{
	size_t off = 0;
	const char *tmp;

	while ((tmp = format_flag(&var, flags)) != NULL) {
		off += snprintf(str + off, size - off, "%s/", tmp);
		assert (off < size);
	}

	/* If there were any flags added... */
	if (off > 0) {
		off--;
		/* ... then remove the last slash. */
		assert(str[off] == '/');
	} 

	str[off] = '\0';

	return (0);
}