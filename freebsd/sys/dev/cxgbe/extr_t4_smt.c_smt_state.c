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
struct smt_entry {int state; } ;

/* Variables and functions */
#define  SMT_STATE_ERROR 129 
#define  SMT_STATE_SWITCHING 128 

__attribute__((used)) static char
smt_state(const struct smt_entry *e)
{
	switch (e->state) {
	case SMT_STATE_SWITCHING: return 'X';
	case SMT_STATE_ERROR: return 'E';
	default: return 'U';
	}
}