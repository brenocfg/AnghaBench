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
struct oid_array {int nr; scalar_t__ oid; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  oid_to_hex (scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 char* strbuf_detach (struct strbuf*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static char *join_sha1_array_hex(struct oid_array *array, char delim)
{
	struct strbuf joined_hexs = STRBUF_INIT;
	int i;

	for (i = 0; i < array->nr; i++) {
		strbuf_addstr(&joined_hexs, oid_to_hex(array->oid + i));
		if (i + 1 < array->nr)
			strbuf_addch(&joined_hexs, delim);
	}

	return strbuf_detach(&joined_hexs, NULL);
}