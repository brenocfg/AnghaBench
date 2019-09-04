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
struct tr2_dst {int /*<<< orphan*/  env_var_name; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tr2_dst_malformed_warning(struct tr2_dst *dst,
				      const char *tgt_value)
{
	struct strbuf buf = STRBUF_INIT;

	strbuf_addf(&buf, "trace2: unknown value for '%s': '%s'",
		    dst->env_var_name, tgt_value);
	warning("%s", buf.buf);

	strbuf_release(&buf);
}