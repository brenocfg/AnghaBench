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
struct write_data {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int write_line_to (int /*<<< orphan*/ ,char const*,size_t) ; 

__attribute__((used)) static int write_line(struct write_data *write_data, const char *line, size_t line_len)
{
	return write_line_to(write_data->buf, line, line_len);
}