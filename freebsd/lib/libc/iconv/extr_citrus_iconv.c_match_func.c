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
struct _citrus_iconv_shared {int /*<<< orphan*/  ci_convname; } ;

/* Variables and functions */
 int strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static __inline int
match_func(struct _citrus_iconv_shared * __restrict ci,
    const char * __restrict key)
{

	return (strcmp(ci->ci_convname, key));
}