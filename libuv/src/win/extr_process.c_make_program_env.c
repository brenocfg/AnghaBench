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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int WCHAR ;
struct TYPE_2__ {int /*<<< orphan*/  wide; scalar_t__ len; int /*<<< orphan*/  wide_eq; } ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CP_UTF8 ; 
 int ERROR_OUTOFMEMORY ; 
 int GetEnvironmentVariableW (int /*<<< orphan*/ ,int*,int) ; 
 int GetLastError () ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int*,int) ; 
 void* alloca (size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int env_strncmp (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int n_required_vars ; 
 int /*<<< orphan*/  qsort (int**,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort_wcscmp ; 
 TYPE_1__* required_vars ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  uv__free (int*) ; 
 int* uv__malloc (int) ; 
 int /*<<< orphan*/  uv_fatal_error (int,char*) ; 
 int /*<<< orphan*/  wcscpy (int*,int /*<<< orphan*/ ) ; 
 int wcslen (int*) ; 
 int /*<<< orphan*/  wmemcpy (int*,int*,int) ; 

int make_program_env(char* env_block[], WCHAR** dst_ptr) {
  WCHAR* dst;
  WCHAR* ptr;
  char** env;
  size_t env_len = 0;
  int len;
  size_t i;
  DWORD var_size;
  size_t env_block_count = 1; /* 1 for null-terminator */
  WCHAR* dst_copy;
  WCHAR** ptr_copy;
  WCHAR** env_copy;
  DWORD* required_vars_value_len = alloca(n_required_vars * sizeof(DWORD*));

  /* first pass: determine size in UTF-16 */
  for (env = env_block; *env; env++) {
    int len;
    if (strchr(*env, '=')) {
      len = MultiByteToWideChar(CP_UTF8,
                                0,
                                *env,
                                -1,
                                NULL,
                                0);
      if (len <= 0) {
        return GetLastError();
      }
      env_len += len;
      env_block_count++;
    }
  }

  /* second pass: copy to UTF-16 environment block */
  dst_copy = (WCHAR*)uv__malloc(env_len * sizeof(WCHAR));
  if (dst_copy == NULL && env_len > 0) {
    return ERROR_OUTOFMEMORY;
  }
  env_copy = alloca(env_block_count * sizeof(WCHAR*));

  ptr = dst_copy;
  ptr_copy = env_copy;
  for (env = env_block; *env; env++) {
    if (strchr(*env, '=')) {
      len = MultiByteToWideChar(CP_UTF8,
                                0,
                                *env,
                                -1,
                                ptr,
                                (int) (env_len - (ptr - dst_copy)));
      if (len <= 0) {
        DWORD err = GetLastError();
        uv__free(dst_copy);
        return err;
      }
      *ptr_copy++ = ptr;
      ptr += len;
    }
  }
  *ptr_copy = NULL;
  assert(env_len == 0 || env_len == (size_t) (ptr - dst_copy));

  /* sort our (UTF-16) copy */
  qsort(env_copy, env_block_count-1, sizeof(wchar_t*), qsort_wcscmp);

  /* third pass: check for required variables */
  for (ptr_copy = env_copy, i = 0; i < n_required_vars; ) {
    int cmp;
    if (!*ptr_copy) {
      cmp = -1;
    } else {
      cmp = env_strncmp(required_vars[i].wide_eq,
                       required_vars[i].len,
                        *ptr_copy);
    }
    if (cmp < 0) {
      /* missing required var */
      var_size = GetEnvironmentVariableW(required_vars[i].wide, NULL, 0);
      required_vars_value_len[i] = var_size;
      if (var_size != 0) {
        env_len += required_vars[i].len;
        env_len += var_size;
      }
      i++;
    } else {
      ptr_copy++;
      if (cmp == 0)
        i++;
    }
  }

  /* final pass: copy, in sort order, and inserting required variables */
  dst = uv__malloc((1+env_len) * sizeof(WCHAR));
  if (!dst) {
    uv__free(dst_copy);
    return ERROR_OUTOFMEMORY;
  }

  for (ptr = dst, ptr_copy = env_copy, i = 0;
       *ptr_copy || i < n_required_vars;
       ptr += len) {
    int cmp;
    if (i >= n_required_vars) {
      cmp = 1;
    } else if (!*ptr_copy) {
      cmp = -1;
    } else {
      cmp = env_strncmp(required_vars[i].wide_eq,
                        required_vars[i].len,
                        *ptr_copy);
    }
    if (cmp < 0) {
      /* missing required var */
      len = required_vars_value_len[i];
      if (len) {
        wcscpy(ptr, required_vars[i].wide_eq);
        ptr += required_vars[i].len;
        var_size = GetEnvironmentVariableW(required_vars[i].wide,
                                           ptr,
                                           (int) (env_len - (ptr - dst)));
        if (var_size != (DWORD) (len - 1)) { /* TODO: handle race condition? */
          uv_fatal_error(GetLastError(), "GetEnvironmentVariableW");
        }
      }
      i++;
    } else {
      /* copy var from env_block */
      len = wcslen(*ptr_copy) + 1;
      wmemcpy(ptr, *ptr_copy, len);
      ptr_copy++;
      if (cmp == 0)
        i++;
    }
  }

  /* Terminate with an extra NULL. */
  assert(env_len == (size_t) (ptr - dst));
  *ptr = L'\0';

  uv__free(dst_copy);
  *dst_ptr = dst;
  return 0;
}