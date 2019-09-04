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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int WideCharToMultiByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 char* uv__malloc (int) ; 

__attribute__((used)) static int fs__wide_to_utf8(WCHAR* w_source_ptr,
                               DWORD w_source_len,
                               char** target_ptr,
                               uint64_t* target_len_ptr) {
  int r;
  int target_len;
  char* target;
  target_len = WideCharToMultiByte(CP_UTF8,
                                   0,
                                   w_source_ptr,
                                   w_source_len,
                                   NULL,
                                   0,
                                   NULL,
                                   NULL);

  if (target_len == 0) {
    return -1;
  }

  if (target_len_ptr != NULL) {
    *target_len_ptr = target_len;
  }

  if (target_ptr == NULL) {
    return 0;
  }

  target = uv__malloc(target_len + 1);
  if (target == NULL) {
    SetLastError(ERROR_OUTOFMEMORY);
    return -1;
  }

  r = WideCharToMultiByte(CP_UTF8,
                          0,
                          w_source_ptr,
                          w_source_len,
                          target,
                          target_len,
                          NULL,
                          NULL);
  assert(r == target_len);
  target[target_len] = '\0';
  *target_ptr = target;
  return 0;
}