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
 int /*<<< orphan*/  pcre2_general_context_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcre2_global_context ; 

void grep_destroy(void)
{
#ifdef USE_LIBPCRE2
	pcre2_general_context_free(pcre2_global_context);
#endif
}