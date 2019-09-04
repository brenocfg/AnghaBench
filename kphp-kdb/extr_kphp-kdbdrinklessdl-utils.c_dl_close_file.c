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

/* Variables and functions */
 int MAX_FN ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  dl_free (int /*<<< orphan*/ *,scalar_t__) ; 
 int* fd ; 
 int /*<<< orphan*/ ** fnames ; 
 scalar_t__* fpos ; 
 scalar_t__* fread_only ; 
 scalar_t__* fsize ; 
 scalar_t__ fsync (int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ *) ; 

void dl_close_file (int x) {
  assert (0 <= x && x < MAX_FN);
  assert (fd[x] != -1);

  if (!fread_only[x]) {
    assert (fsync (fd[x]) >= 0);
  } else {
    fread_only[x] = 0;
  }
  assert (close (fd[x]) >= 0);
  fd[x] = -1;

  fsize[x] = 0;
  fpos[x] = 0;
  dl_free (fnames[x], strlen (fnames[x]) + 1);
  fnames[x] = NULL;
}