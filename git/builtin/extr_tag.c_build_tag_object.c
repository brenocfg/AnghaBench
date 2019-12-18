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
struct strbuf {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ do_sign (struct strbuf*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tag_type ; 
 scalar_t__ write_object_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct object_id*) ; 

__attribute__((used)) static int build_tag_object(struct strbuf *buf, int sign, struct object_id *result)
{
	if (sign && do_sign(buf) < 0)
		return error(_("unable to sign the tag"));
	if (write_object_file(buf->buf, buf->len, tag_type, result) < 0)
		return error(_("unable to write tag file"));
	return 0;
}