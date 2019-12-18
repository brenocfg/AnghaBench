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
typedef  int /*<<< orphan*/  uint64_t ;
struct sbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  field_desc_show (struct sbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tp_la0 ; 

__attribute__((used)) static void
tp_la_show(struct sbuf *sb, uint64_t *p, int idx)
{

	field_desc_show(sb, *p, tp_la0);
}