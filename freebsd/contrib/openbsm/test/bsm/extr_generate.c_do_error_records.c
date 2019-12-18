#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  error_number; int /*<<< orphan*/  error_name; } ;

/* Variables and functions */
 TYPE_1__* error_list ; 
 int error_list_count ; 
 int /*<<< orphan*/  generate_error_record (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_error_records(const char *directory)
{
	int i;

	for (i = 0; i < error_list_count; i++)
		generate_error_record(directory, error_list[i].error_name,
		    error_list[i].error_number);
}