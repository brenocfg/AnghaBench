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
struct cpp_demangle_data {char* cur; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char const*,int) ; 

__attribute__((used)) static int
cpp_demangle_read_offset_number(struct cpp_demangle_data *ddata)
{
	bool negative;
	const char *start;

	if (ddata == NULL || *ddata->cur == '\0')
		return (0);

	/* offset could be negative */
	if (*ddata->cur == 'n') {
		negative = true;
		start = ddata->cur + 1;
	} else {
		negative = false;
		start = ddata->cur;
	}

	while (*ddata->cur != '_')
		++ddata->cur;

	if (negative && !cpp_demangle_push_str(ddata, "-", 1))
		return (0);

	assert(start != NULL);

	if (!cpp_demangle_push_str(ddata, start, ddata->cur - start))
		return (0);
	if (!cpp_demangle_push_str(ddata, " ", 1))
		return (0);

	++ddata->cur;

	return (1);
}