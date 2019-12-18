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
struct archive_string_conv {int dummy; } ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 int best_effort_strncat_from_utf16 (struct archive_string*,void const*,size_t,struct archive_string_conv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
best_effort_strncat_from_utf16le(struct archive_string *as, const void *_p,
    size_t bytes, struct archive_string_conv *sc)
{
	return (best_effort_strncat_from_utf16(as, _p, bytes, sc, 0));
}