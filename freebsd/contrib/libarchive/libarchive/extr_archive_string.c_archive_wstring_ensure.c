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
typedef  int /*<<< orphan*/  wchar_t ;
struct archive_wstring {int dummy; } ;
struct archive_string {int dummy; } ;

/* Variables and functions */
 scalar_t__ archive_string_ensure (struct archive_string*,size_t) ; 

struct archive_wstring *
archive_wstring_ensure(struct archive_wstring *as, size_t s)
{
	return (struct archive_wstring *)
		archive_string_ensure((struct archive_string *)as,
					s * sizeof(wchar_t));
}