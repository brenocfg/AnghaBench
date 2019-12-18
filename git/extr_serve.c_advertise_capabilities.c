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
struct strbuf {scalar_t__ len; int /*<<< orphan*/  buf; } ;
struct protocol_capability {int /*<<< orphan*/  name; scalar_t__ (* advertise ) (int /*<<< orphan*/ ,struct strbuf*) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct protocol_capability*) ; 
 struct strbuf STRBUF_INIT ; 
 struct protocol_capability* capabilities ; 
 int /*<<< orphan*/  packet_flush (int) ; 
 int /*<<< orphan*/  packet_write (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_addbuf (struct strbuf*,struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct strbuf*) ; 
 int /*<<< orphan*/  the_repository ; 

__attribute__((used)) static void advertise_capabilities(void)
{
	struct strbuf capability = STRBUF_INIT;
	struct strbuf value = STRBUF_INIT;
	int i;

	for (i = 0; i < ARRAY_SIZE(capabilities); i++) {
		struct protocol_capability *c = &capabilities[i];

		if (c->advertise(the_repository, &value)) {
			strbuf_addstr(&capability, c->name);

			if (value.len) {
				strbuf_addch(&capability, '=');
				strbuf_addbuf(&capability, &value);
			}

			strbuf_addch(&capability, '\n');
			packet_write(1, capability.buf, capability.len);
		}

		strbuf_reset(&capability);
		strbuf_reset(&value);
	}

	packet_flush(1);
	strbuf_release(&capability);
	strbuf_release(&value);
}