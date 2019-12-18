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
struct tcphdr {int dummy; } ;
typedef  int /*<<< orphan*/  ipfw_insn ;

/* Variables and functions */
 int flags_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcpopts_parse (struct tcphdr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
tcpopts_match(struct tcphdr *tcp, ipfw_insn *cmd)
{

	return (flags_match(cmd, tcpopts_parse(tcp, NULL)));
}