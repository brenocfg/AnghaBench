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
typedef  int /*<<< orphan*/  uintmax_t ;
struct sbuf {int dummy; } ;
struct g_provider {scalar_t__ stripesize; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  error; int /*<<< orphan*/  ace; int /*<<< orphan*/  acw; int /*<<< orphan*/  acr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,struct g_provider*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_confdot_provider(struct sbuf *sb, struct g_provider *pp)
{

	sbuf_printf(sb, "z%p [shape=hexagon,label=\"%s\\nr%dw%de%d\\nerr#%d\\n"
	    "sector=%u\\nstripe=%ju\"];\n", pp, pp->name, pp->acr, pp->acw,
	    pp->ace, pp->error, pp->sectorsize, (uintmax_t)pp->stripesize);
}