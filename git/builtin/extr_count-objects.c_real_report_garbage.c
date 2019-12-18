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
struct stat {scalar_t__ st_size; } ;

/* Variables and functions */
 char* bits_to_msg (unsigned int) ; 
 int /*<<< orphan*/  garbage ; 
 int /*<<< orphan*/  size_garbage ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  warning (char*,char const*,char const*) ; 

__attribute__((used)) static void real_report_garbage(unsigned seen_bits, const char *path)
{
	struct stat st;
	const char *desc = bits_to_msg(seen_bits);

	if (!desc)
		return;

	if (!stat(path, &st))
		size_garbage += st.st_size;
	warning("%s: %s", desc, path);
	garbage++;
}