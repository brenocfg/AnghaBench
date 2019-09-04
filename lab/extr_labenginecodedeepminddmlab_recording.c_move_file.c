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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EXDEV ; 
 int copy_fp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int rename (char const*,char const*) ; 
 scalar_t__ unlink (char const*) ; 

__attribute__((used)) static bool move_file(const char* src, const char* dest) {
  FILE* src_file;
  FILE* dest_file;

  int rename_code = rename(src, dest);
  if (rename_code == 0) {
    return true;
  }

  // Continue only if it's an invalid cross-device link error.
  if (errno != EXDEV) {
    return rename_code;
  }

  // Rename failed, copy the file and delete the original.
  if (!(src_file = fopen(src, "r"))) {
    return false;  // 'fopen' sets errno.
  }

  if (!(dest_file = fopen(dest, "w"))) {
    fclose(src_file);
    return false;  // 'fopen' sets errno.
  }

  int copy_fp_code = copy_fp(src_file, dest_file);
  fclose(src_file);
  fclose(dest_file);

  if (copy_fp_code == 0) {
    return unlink(src) == 0;
  } else {
    unlink(dest);
    return copy_fp_code == 0;
  }
}