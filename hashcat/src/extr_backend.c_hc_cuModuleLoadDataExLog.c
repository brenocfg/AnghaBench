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
typedef  int /*<<< orphan*/  hashcat_ctx_t ;
typedef  int /*<<< orphan*/  CUmodule ;
typedef  int /*<<< orphan*/  CUjit_option ;

/* Variables and functions */
 int /*<<< orphan*/  CU_JIT_ERROR_LOG_BUFFER ; 
 int /*<<< orphan*/  CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES ; 
 int /*<<< orphan*/  CU_JIT_INFO_LOG_BUFFER ; 
 int /*<<< orphan*/  CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES ; 
 int /*<<< orphan*/  CU_JIT_LOG_VERBOSE ; 
 int /*<<< orphan*/  CU_JIT_TARGET_FROM_CUCONTEXT ; 
 scalar_t__ LOG_SIZE ; 
 int hc_cuModuleLoadDataEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void const*,int,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  hcfree (char*) ; 
 scalar_t__ hcmalloc (scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 scalar_t__ strlen (char*) ; 

int hc_cuModuleLoadDataExLog (hashcat_ctx_t *hashcat_ctx, CUmodule *module, const void *image)
{
  #define LOG_SIZE 8192

  char *info_log  = (char *) hcmalloc (LOG_SIZE);
  char *error_log = (char *) hcmalloc (LOG_SIZE);

  CUjit_option opts[6];
  void *vals[6];

  opts[0] = CU_JIT_TARGET_FROM_CUCONTEXT;
  vals[0] = (void *) 0;

  opts[1] = CU_JIT_LOG_VERBOSE;
  vals[1] = (void *) 1;

  opts[2] = CU_JIT_INFO_LOG_BUFFER;
  vals[2] = (void *) info_log;

  opts[3] = CU_JIT_INFO_LOG_BUFFER_SIZE_BYTES;
  vals[3] = (void *) LOG_SIZE;

  opts[4] = CU_JIT_ERROR_LOG_BUFFER;
  vals[4] = (void *) error_log;

  opts[5] = CU_JIT_ERROR_LOG_BUFFER_SIZE_BYTES;
  vals[5] = (void *) LOG_SIZE;

  const int rc_cuModuleLoadDataEx = hc_cuModuleLoadDataEx (hashcat_ctx, module, image, 6, opts, vals);

  #if defined (DEBUG)
  printf ("cuModuleLoadDataEx() Info Log (%d):\n%s\n\n",  (int) strlen (info_log),  info_log);
  printf ("cuModuleLoadDataEx() Error Log (%d):\n%s\n\n", (int) strlen (error_log), error_log);
  #else
  if (rc_cuModuleLoadDataEx == -1)
  {
    printf ("cuModuleLoadDataEx() Info Log (%d):\n%s\n\n",  (int) strlen (info_log),  info_log);
    printf ("cuModuleLoadDataEx() Error Log (%d):\n%s\n\n", (int) strlen (error_log), error_log);
  }
  #endif

  hcfree (info_log);
  hcfree (error_log);

  return rc_cuModuleLoadDataEx;
}