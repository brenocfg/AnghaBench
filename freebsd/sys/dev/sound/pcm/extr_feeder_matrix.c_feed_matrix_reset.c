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
typedef  int uint32_t ;
struct feed_matrix_info {TYPE_1__* matrix; } ;
struct TYPE_2__ {int mul; scalar_t__ shift; int /*<<< orphan*/ * chn; } ;

/* Variables and functions */
 int /*<<< orphan*/  SND_CHN_T_EOF ; 

__attribute__((used)) static void
feed_matrix_reset(struct feed_matrix_info *info)
{
	uint32_t i, j;

	for (i = 0; i < (sizeof(info->matrix) / sizeof(info->matrix[0])); i++) {
		for (j = 0;
		    j < (sizeof(info->matrix[i].chn) /
		    sizeof(info->matrix[i].chn[0])); j++) {
			info->matrix[i].chn[j] = SND_CHN_T_EOF;
		}
		info->matrix[i].mul   = 1;
		info->matrix[i].shift = 0;
	}
}