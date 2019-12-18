#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t size; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char*,int) ; 
 char* strstr (char const*,char*) ; 

__attribute__((used)) static void overwrite_filemode(const char *expected, git_buf *actual)
{
	size_t offset;
	char *found;

	found = strstr(expected, "100644");
	if (!found)
		return;

	offset = ((const char *)found) - expected;
	if (actual->size < offset + 6)
		return;

	if (memcmp(&actual->ptr[offset], "100644", 6) != 0)
		memcpy(&actual->ptr[offset], "100644", 6);
}