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
struct _zone {scalar_t__ z_begin; scalar_t__ z_end; } ;
struct _parse_state {scalar_t__ ps_u_imm; } ;
struct _memstream {int dummy; } ;

/* Variables and functions */
 char T_IMM ; 
 char get_tok (struct _memstream*,struct _parse_state*) ; 

__attribute__((used)) static int
parse_zone(struct _memstream *ms, struct _parse_state *ps, struct _zone *z)
{

	if (get_tok(ms, ps) != T_IMM)
		return (-1);
	z->z_begin = ps->ps_u_imm;
	if (get_tok(ms, ps) != '-')
		return (-1);
	if (get_tok(ms, ps) != T_IMM)
		return (-1);
	z->z_end = ps->ps_u_imm;

	if (z->z_begin > z->z_end)
		return (-1);

	return (0);
}