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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  pattern_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_chunk_range (int /*<<< orphan*/ *,int,int*,int*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  marker_fill (int /*<<< orphan*/ *,int,size_t,int) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 int /*<<< orphan*/  outfd ; 
 scalar_t__ p_file ; 
 int /*<<< orphan*/  pwrite (int /*<<< orphan*/ ,void*,size_t,int) ; 

__attribute__((used)) static void
write_chunk(pattern_t* p_pat, int chunk_idx, int is_follower)
{
  uint32_t chunk_start, chunk_end;
  get_chunk_range(p_pat, chunk_idx, &chunk_start, &chunk_end);
  size_t size =  chunk_end - chunk_start;
  uint64_t* buf = malloc(size);
  marker_fill(buf, chunk_start, size, is_follower);
#if USE_MMAP
  memcpy((void*)( (char*)p_file + chunk_start ), (void*)buf, size);
#else
  pwrite(outfd, (void*)buf, size, chunk_start);
#endif
  free(buf);
}