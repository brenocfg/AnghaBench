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
struct strbuf {int dummy; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  abbrev ; 
 int /*<<< orphan*/  find_unique_abbrev (struct object_id const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_suffix(int depth, const struct object_id *oid, struct strbuf *dst)
{
	strbuf_addf(dst, "-%d-g%s", depth, find_unique_abbrev(oid, abbrev));
}