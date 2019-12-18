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
struct lev_filesys_xfs_file_chunk {int part; int size; int /*<<< orphan*/ * data; } ;
struct TYPE_2__ {int chunk; int chunks; size_t M; int /*<<< orphan*/  name; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__ curfile ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  process_file () ; 
 int /*<<< orphan*/  vkprintf (int,char*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void filesys_xfs_file_chunk (struct lev_filesys_xfs_file_chunk *E) {
  assert (E->part == curfile.chunk);
  assert (E->part < curfile.chunks);
  int chunk_size = E->size + 1;
  assert (E->part == curfile.chunks - 1 || chunk_size == 0x10000);
  memcpy (&curfile.data[curfile.M], &E->data[0], chunk_size);
  curfile.M += chunk_size;
  curfile.chunk++;
  vkprintf (4, "%d chunk of %d chunks readed (%s).\n", (int) curfile.chunk, (int) curfile.chunks, curfile.name);
  if (curfile.chunk == curfile.chunks) {
    process_file ();
  }
}