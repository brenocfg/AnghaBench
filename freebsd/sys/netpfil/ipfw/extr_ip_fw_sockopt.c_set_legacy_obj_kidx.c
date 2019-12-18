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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct opcode_obj_rewrite {int /*<<< orphan*/  (* update ) (int /*<<< orphan*/ *,int) ;struct named_object* (* find_bykidx ) (struct ip_fw_chain*,int) ;} ;
struct named_object {int /*<<< orphan*/  name; } ;
struct ip_fw_rule0 {int cmd_len; int /*<<< orphan*/ * cmd; } ;
struct ip_fw_chain {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int F_LEN (int /*<<< orphan*/ *) ; 
 struct opcode_obj_rewrite* find_op_rw (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 long strtol (int /*<<< orphan*/ ,char**,int) ; 
 struct named_object* stub1 (struct ip_fw_chain*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
set_legacy_obj_kidx(struct ip_fw_chain *ch, struct ip_fw_rule0 *rule)
{
	struct opcode_obj_rewrite *rw;
	struct named_object *no;
	ipfw_insn *cmd;
	char *end;
	long val;
	int cmdlen, error, l;
	uint16_t kidx, uidx;
	uint8_t subtype;

	error = 0;

	l = rule->cmd_len;
	cmd = rule->cmd;
	cmdlen = 0;
	for ( ;	l > 0 ; l -= cmdlen, cmd += cmdlen) {
		cmdlen = F_LEN(cmd);

		/* Check if is index in given opcode */
		rw = find_op_rw(cmd, &kidx, &subtype);
		if (rw == NULL)
			continue;

		/* Try to find referenced kernel object */
		no = rw->find_bykidx(ch, kidx);
		if (no == NULL)
			continue;

		val = strtol(no->name, &end, 10);
		if (*end == '\0' && val < 65535) {
			uidx = val;
		} else {

			/*
			 * We are called via legacy opcode.
			 * Save error and show table as fake number
			 * not to make ipfw(8) hang.
			 */
			uidx = 65535;
			error = 2;
		}

		rw->update(cmd, uidx);
	}

	return (error);
}