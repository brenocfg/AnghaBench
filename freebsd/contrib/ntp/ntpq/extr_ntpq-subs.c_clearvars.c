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
struct parse {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  doclearvlist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_varlist ; 

__attribute__((used)) static void
clearvars(
	struct parse *pcmd,
	FILE *fp
	)
{
	doclearvlist(g_varlist);
}