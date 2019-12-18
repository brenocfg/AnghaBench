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
struct archive_string {int dummy; } ;

/* Variables and functions */
 struct archive_string* archive_strncat (struct archive_string*,void const*,int) ; 

struct archive_string *
archive_strcat(struct archive_string *as, const void *p)
{
	/* strcat is just strncat without an effective limit. 
	 * Assert that we'll never get called with a source
	 * string over 16MB.
	 * TODO: Review all uses of strcat in the source
	 * and try to replace them with strncat().
	 */
	return archive_strncat(as, p, 0x1000000);
}