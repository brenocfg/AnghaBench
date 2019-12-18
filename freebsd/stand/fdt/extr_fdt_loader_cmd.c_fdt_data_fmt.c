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

/* Variables and functions */
 int fdt_data_bytes (void const*,int,char**) ; 
 int fdt_data_cell (void const*,int,char**) ; 
 int fdt_data_str (void const*,int,int,char**) ; 
 scalar_t__ fdt_isprint (void const*,int,int*) ; 

__attribute__((used)) static int
fdt_data_fmt(const void *data, int len, char **buf)
{
	int count;

	if (len == 0) {
		*buf = NULL;
		return (1);
	}

	if (fdt_isprint(data, len, &count))
		return (fdt_data_str(data, len, count, buf));

	else if ((len % 4) == 0)
		return (fdt_data_cell(data, len, buf));

	else
		return (fdt_data_bytes(data, len, buf));
}