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
struct dh {unsigned int key_size; unsigned int p_size; unsigned int q_size; unsigned int g_size; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned int dh_data_size(const struct dh *p)
{
	return p->key_size + p->p_size + p->q_size + p->g_size;
}