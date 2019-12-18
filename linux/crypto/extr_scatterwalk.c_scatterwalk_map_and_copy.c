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
struct scatter_walk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_copychunks (void*,struct scatter_walk*,unsigned int,int) ; 
 int /*<<< orphan*/  scatterwalk_done (struct scatter_walk*,int,int /*<<< orphan*/ ) ; 
 struct scatterlist* scatterwalk_ffwd (struct scatterlist*,struct scatterlist*,unsigned int) ; 
 int /*<<< orphan*/  scatterwalk_start (struct scatter_walk*,struct scatterlist*) ; 

void scatterwalk_map_and_copy(void *buf, struct scatterlist *sg,
			      unsigned int start, unsigned int nbytes, int out)
{
	struct scatter_walk walk;
	struct scatterlist tmp[2];

	if (!nbytes)
		return;

	sg = scatterwalk_ffwd(tmp, sg, start);

	scatterwalk_start(&walk, sg);
	scatterwalk_copychunks(buf, &walk, nbytes, out);
	scatterwalk_done(&walk, out, 0);
}