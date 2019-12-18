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
struct checkdiff_t {long lineno; } ;

/* Variables and functions */

__attribute__((used)) static void checkdiff_consume_hunk(void *priv,
				   long ob, long on, long nb, long nn,
				   const char *func, long funclen)

{
	struct checkdiff_t *data = priv;
	data->lineno = nb - 1;
}