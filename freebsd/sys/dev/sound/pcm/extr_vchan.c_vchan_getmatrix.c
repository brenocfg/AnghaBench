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
typedef  int /*<<< orphan*/  uint32_t ;
struct pcmchan_matrix {int dummy; } ;
typedef  int /*<<< orphan*/  kobj_t ;

/* Variables and functions */
 struct pcmchan_matrix* feeder_matrix_format_map (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pcmchan_matrix *
vchan_getmatrix(kobj_t obj, void *data, uint32_t format)
{

	return (feeder_matrix_format_map(format));
}