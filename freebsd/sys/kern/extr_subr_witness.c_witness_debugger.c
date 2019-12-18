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
struct stack {int dummy; } ;
struct sbuf {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KDB_WHY_WITNESS ; 
 int /*<<< orphan*/  SBUF_FIXEDLEN ; 
 int /*<<< orphan*/  kdb_enter (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_set_drain (struct sbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_save (struct stack*) ; 
 int /*<<< orphan*/  stack_sbuf_print_ddb (struct sbuf*,struct stack*) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 
 scalar_t__ witness_kdb ; 
 int /*<<< orphan*/  witness_output (char*) ; 
 int /*<<< orphan*/  witness_output_drain ; 
 scalar_t__ witness_trace ; 

__attribute__((used)) static void
witness_debugger(int cond, const char *msg)
{
	char buf[32];
	struct sbuf sb;
	struct stack st;

	if (!cond)
		return;

	if (witness_trace) {
		sbuf_new(&sb, buf, sizeof(buf), SBUF_FIXEDLEN);
		sbuf_set_drain(&sb, witness_output_drain, NULL);

		stack_zero(&st);
		stack_save(&st);
		witness_output("stack backtrace:\n");
		stack_sbuf_print_ddb(&sb, &st);

		sbuf_finish(&sb);
	}

#ifdef KDB
	if (witness_kdb)
		kdb_enter(KDB_WHY_WITNESS, msg);
#endif
}