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
struct match_file {int /*<<< orphan*/  pathname; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_mstring_get_wcs (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const**) ; 
 int wcscmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
cmp_node_wcs(const struct archive_rb_node *n1,
    const struct archive_rb_node *n2)
{
	struct match_file *f1 = (struct match_file *)(uintptr_t)n1;
	struct match_file *f2 = (struct match_file *)(uintptr_t)n2;
	const wchar_t *p1, *p2;

	archive_mstring_get_wcs(NULL, &(f1->pathname), &p1);
	archive_mstring_get_wcs(NULL, &(f2->pathname), &p2);
	if (p1 == NULL)
		return (1);
	if (p2 == NULL)
		return (-1);
	return (wcscmp(p1, p2));
}