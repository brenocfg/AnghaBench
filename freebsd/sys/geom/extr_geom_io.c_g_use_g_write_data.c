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
struct g_consumer {int dummy; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
 int g_write_data (struct g_consumer*,int /*<<< orphan*/ ,void*,int) ; 

int
g_use_g_write_data(void *devfd, off_t loc, void *buf, int size)
{

	return (g_write_data((struct g_consumer *)devfd, loc, buf, size));
}