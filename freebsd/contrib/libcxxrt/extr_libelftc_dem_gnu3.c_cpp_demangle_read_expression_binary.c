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
struct cpp_demangle_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpp_demangle_push_str (struct cpp_demangle_data*,char const*,size_t) ; 
 int cpp_demangle_read_expression (struct cpp_demangle_data*) ; 

__attribute__((used)) static int
cpp_demangle_read_expression_binary(struct cpp_demangle_data *ddata,
    const char *name, size_t len)
{

	if (ddata == NULL || name == NULL || len == 0)
		return (0);
	if (!cpp_demangle_read_expression(ddata))
		return (0);
	if (!cpp_demangle_push_str(ddata, name, len))
		return (0);

	return (cpp_demangle_read_expression(ddata));
}