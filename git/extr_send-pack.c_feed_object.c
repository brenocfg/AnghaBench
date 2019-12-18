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
struct object_id {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  OBJECT_INFO_SKIP_FETCH_OBJECT ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  has_object_file_with_flags (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (struct object_id const*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void feed_object(const struct object_id *oid, FILE *fh, int negative)
{
	if (negative &&
	    !has_object_file_with_flags(oid, OBJECT_INFO_SKIP_FETCH_OBJECT))
		return;

	if (negative)
		putc('^', fh);
	fputs(oid_to_hex(oid), fh);
	putc('\n', fh);
}