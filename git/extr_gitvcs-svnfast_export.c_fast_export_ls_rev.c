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
typedef  int /*<<< orphan*/  uint32_t ;
struct strbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_response_line () ; 
 int /*<<< orphan*/  ls_from_rev (int /*<<< orphan*/ ,char const*) ; 
 int parse_ls_response (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct strbuf*) ; 

int fast_export_ls_rev(uint32_t rev, const char *path,
				uint32_t *mode, struct strbuf *dataref)
{
	ls_from_rev(rev, path);
	return parse_ls_response(get_response_line(), mode, dataref);
}