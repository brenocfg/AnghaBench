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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/  tmp ;
struct archive_string {int dummy; } ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  add_pax_attr (struct archive_string*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_int (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
add_pax_attr_int(struct archive_string *as, const char *key, int64_t value)
{
	char tmp[1 + 3 * sizeof(value)];

	tmp[sizeof(tmp) - 1] = 0;
	add_pax_attr(as, key, format_int(tmp + sizeof(tmp) - 1, value));
}