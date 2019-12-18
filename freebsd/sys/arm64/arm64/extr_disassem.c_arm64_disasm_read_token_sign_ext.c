#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int ;
struct arm64_insn {TYPE_1__* tokens; } ;
struct TYPE_2__ {int len; int pos; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARM64_MAX_TOKEN_CNT ; 
 int EINVAL ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int
arm64_disasm_read_token_sign_ext(struct arm64_insn *insn, u_int opcode,
    const char *token, int *val)
{
	int i;
	int msk;

	for (i = 0; i < ARM64_MAX_TOKEN_CNT; i++) {
		if (strcmp(insn->tokens[i].name, token) == 0) {
			msk = (1 << insn->tokens[i].len) - 1;
			*val = ((opcode >> insn->tokens[i].pos) & msk);

			/* If last bit is 1, sign-extend the value */
			if (*val & (1 << (insn->tokens[i].len - 1)))
				*val |= ~msk;

			return (0);
		}
	}

	return (EINVAL);
}