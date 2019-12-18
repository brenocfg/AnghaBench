#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  len; } ;
struct mailinfo {TYPE_1__ inbody_header_accum; int /*<<< orphan*/  s_hdr_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  check_header (struct mailinfo*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_reset (TYPE_1__*) ; 

__attribute__((used)) static void flush_inbody_header_accum(struct mailinfo *mi)
{
	if (!mi->inbody_header_accum.len)
		return;
	if (!check_header(mi, &mi->inbody_header_accum, mi->s_hdr_data, 0))
		BUG("inbody_header_accum, if not empty, must always contain a valid in-body header");
	strbuf_reset(&mi->inbody_header_accum);
}