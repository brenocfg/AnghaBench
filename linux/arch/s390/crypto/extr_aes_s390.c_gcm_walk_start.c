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
struct scatterlist {int dummy; } ;
struct gcm_sg_walk {unsigned int walk_bytes_remain; int /*<<< orphan*/  walk; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct gcm_sg_walk*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_start (int /*<<< orphan*/ *,struct scatterlist*) ; 

__attribute__((used)) static void gcm_walk_start(struct gcm_sg_walk *gw, struct scatterlist *sg,
			   unsigned int len)
{
	memset(gw, 0, sizeof(*gw));
	gw->walk_bytes_remain = len;
	scatterwalk_start(&gw->walk, sg);
}