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
typedef  unsigned long long uint64_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int TPLA_SIZE ; 
 int /*<<< orphan*/  field_desc_show (struct sbuf*,unsigned long long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*) ; 
 int /*<<< orphan*/  tp_la0 ; 
 int /*<<< orphan*/  tp_la1 ; 
 int /*<<< orphan*/  tp_la2 ; 

__attribute__((used)) static void
tp_la_show3(struct sbuf *sb, uint64_t *p, int idx)
{

	if (idx)
		sbuf_printf(sb, "\n");
	field_desc_show(sb, p[0], tp_la0);
	if (idx < (TPLA_SIZE / 2 - 1) || p[1] != ~0ULL)
		field_desc_show(sb, p[1], (p[0] & (1 << 17)) ? tp_la2 : tp_la1);
}