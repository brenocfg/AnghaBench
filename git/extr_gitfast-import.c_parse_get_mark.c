#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  oid; } ;
struct object_entry {TYPE_1__ idx; } ;
typedef  int /*<<< orphan*/  output ;
struct TYPE_6__ {char const* buf; } ;
struct TYPE_5__ {scalar_t__ hexsz; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MAX_HEXSZ ; 
 int /*<<< orphan*/  cat_blob_write (char*,scalar_t__) ; 
 TYPE_3__ command_buf ; 
 int /*<<< orphan*/  die (char*,char const*) ; 
 struct object_entry* find_mark (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oid_to_hex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_mark_ref_eol (char const*) ; 
 TYPE_2__* the_hash_algo ; 
 int /*<<< orphan*/  xsnprintf (char*,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void parse_get_mark(const char *p)
{
	struct object_entry *oe;
	char output[GIT_MAX_HEXSZ + 2];

	/* get-mark SP <object> LF */
	if (*p != ':')
		die("Not a mark: %s", p);

	oe = find_mark(parse_mark_ref_eol(p));
	if (!oe)
		die("Unknown mark: %s", command_buf.buf);

	xsnprintf(output, sizeof(output), "%s\n", oid_to_hex(&oe->idx.oid));
	cat_blob_write(output, the_hash_algo->hexsz + 1);
}