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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_chunk_range (int /*<<< orphan*/ *,int,size_t*,size_t*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  marker_fill (int /*<<< orphan*/ *,size_t,size_t,int) ; 
 int /*<<< orphan*/  outfd ; 
 int /*<<< orphan*/  pwrite (int /*<<< orphan*/ ,void*,size_t,size_t) ; 

__attribute__((used)) static void
write_chunk(pattern_t* p_pat, int chunk_idx, int thread_num)
{
  uint32_t chunk_start, chunk_end;
  get_chunk_range(p_pat, chunk_idx, &chunk_start, &chunk_end);
  size_t size =  chunk_end - chunk_start;
  uint64_t* buf = malloc(size);
  marker_fill(buf, chunk_start, size, thread_num);
  pwrite(outfd, (void*)buf, size, chunk_start);
  free(buf);
}