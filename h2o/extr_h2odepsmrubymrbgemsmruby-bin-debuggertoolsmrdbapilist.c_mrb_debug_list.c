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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  source_file ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_debug_context ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_DEBUG_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  MRB_DEBUG_OK ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  show_lines (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  source_file_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * source_file_new (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strrchr (char*,char) ; 

int32_t
mrb_debug_list(mrb_state *mrb, mrb_debug_context *dbg, char *filename, uint16_t line_min, uint16_t line_max)
{
  char *ext;
  source_file *file;

  if (mrb == NULL || dbg == NULL || filename == NULL) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  ext = strrchr(filename, '.');

  if (ext == NULL || strcmp(ext, ".rb")) {
    printf("List command only supports .rb file.\n");
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  if (line_min > line_max) {
    return MRB_DEBUG_INVALID_ARGUMENT;
  }

  if ((file = source_file_new(mrb, dbg, filename)) != NULL) {
    show_lines(file, line_min, line_max);
    source_file_free(mrb, file);
    return MRB_DEBUG_OK;
  }
  else {
    printf("Invalid source file named %s.\n", filename);
    return MRB_DEBUG_INVALID_ARGUMENT;
  }
}